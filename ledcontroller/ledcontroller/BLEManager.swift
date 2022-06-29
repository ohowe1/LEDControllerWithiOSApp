//
//  BLEManager.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/27/22.
//

import Foundation
import CoreBluetooth

class BLEManager: NSObject, ObservableObject {
  @Published var isConnected: Bool = false
  
  let servicesUUID = CBUUID(string: "96cf1825-f046-4266-8a68-14c04101c9b7")
  let characteristicUUID = CBUUID(string: "398453f9-14a3-4412-908c-aedfebb4608c")
  
  var central: CBCentralManager!
  
  var ledController: CBPeripheral?
  var transferCharacteristic: CBCharacteristic?
  
  override init() {
    super.init()
    
    central = CBCentralManager(delegate: self, queue: .main, options: [
      CBCentralManagerOptionShowPowerAlertKey: true,
    ])
  }
  
  func retrieveClue() {
    let connectedPeripherals: [CBPeripheral] = (central.retrieveConnectedPeripherals(withServices: [servicesUUID]))
    
    if let connectedPeripheral = connectedPeripherals.last {
      self.ledController = connectedPeripheral
      central.connect(connectedPeripheral, options: nil)
    } else {
      central.scanForPeripherals(withServices: [servicesUUID],
                                        options: [CBCentralManagerScanOptionAllowDuplicatesKey: true])
    }
  }
  
  
  func send(_ data: Data) {
    guard let peripheral = ledController, let characteristic = transferCharacteristic else {
      print("Tried to send data without connecting")
      return
    }
    
    peripheral.writeValue(data, for: characteristic, type: .withoutResponse)
  }
  
  func cancel() {
    isConnected = false
    guard let ledController = ledController else {
      return
    }
    central.cancelPeripheralConnection(ledController)
  }
  
}

extension BLEManager: CBCentralManagerDelegate {
  func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
    print("Callback 1")
    guard RSSI.intValue >= -70 else {
      print(RSSI.intValue)
      cancel()
      return
    }
    central.stopScan()
    
    // 10 second timeout
//    Timer.scheduledTimer(withTimeInterval: 10, repeats: false, block: { _ in
//      self.cancel()
//    })
    ledController = peripheral
    central.connect(peripheral, options: nil)
    print("Connecting...")
  }
  
  func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
    print("Connected")
    peripheral.delegate = self
    peripheral.discoverServices([servicesUUID])
    print("Discovering services...")
  }
  
  func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
    if let error = error {
      print(error)
    }
    cancel()
  }
  
  func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
    if let error = error {
      print(error)
    }
    cancel()
  }
  
  func centralManagerDidUpdateState(_ central: CBCentralManager) {
    print("State changed")
    switch central.state {
    case .poweredOn:
      retrieveClue()
    default:
      break;
    }
  }
}

extension BLEManager: CBPeripheralDelegate {
  func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
    if let error = error {
      print(error)
      cancel()
    }
    
    guard let services = peripheral.services, let service = services.last else {
      return
    }
    
    peripheral.discoverCharacteristics([characteristicUUID], for: service)
    print("Services discovered")
  }
  
  func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
    print("Characteristics discovered")
    if let error = error {
      print(error)
      cancel()
      return
    }
    
    guard let characteristics = service.characteristics else {
      return
    }
    
    guard let characteristic = characteristics.first(where: { chara in
      return chara.uuid == characteristicUUID
    }) else {
      return
    }
    
    peripheral.setNotifyValue(true, for: characteristic)
    transferCharacteristic = characteristic
    self.isConnected = true
  }
}
