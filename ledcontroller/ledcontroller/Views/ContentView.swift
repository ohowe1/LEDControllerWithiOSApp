//
//  ContentView.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/27/22.
//

import SwiftUI

struct ContentView: View {
  @State var ledMode: LEDMode = AnimatedRainbowMode()
  @ObservedObject var bleManager: BLEManager = BLEManager()
  
  var body: some View {
    VStack {
      if bleManager.isConnected {
        if ledMode is StillColorMode {
          Button(action: { ledMode = AnimatedRainbowMode() }) {
            Text("Switch to Animated Rainbow Mode")
          }
          StillColorModeView(modeState: ledMode as! StillColorMode)
        } else if ledMode is AnimatedRainbowMode {
          Button(action: { ledMode = StillColorMode() }) {
            Text("Switch to Still Color Mode")
          }
          AnimatedRainbowModeView(modeState: ledMode as! AnimatedRainbowMode)
        }
        Button(action: {
          if bleManager.isConnected {
            var data: Data = Data([ledMode.id])
            data.append(ledMode.data)
            bleManager.send(data)
          }
          
        }) {
          Text("Send")
        }
        .padding(.vertical)
      } else {
        Text("Connecting to device")
        ProgressView()
      }
    }
  }
}

struct ContentView_Previews: PreviewProvider {
  static var previews: some View {
    ContentView()
  }
}
