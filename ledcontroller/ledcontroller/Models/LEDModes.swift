//
//  LEDModes.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/27/22.
//

import Foundation
import SwiftUI

extension Numeric {
  var data: Data {
    var source = self
    return Data(bytes: &source, count: MemoryLayout<Self>.size)
  }
}

protocol LEDMode {
  var id: UInt8 { get }
  var data: Data { get }
}

class StillColorMode: LEDMode, ObservableObject {
  var color: Color = .white
  
  var id: UInt8 = 0x01
  var data: Data {
    
    var components: [CGFloat] = color.cgColor?.components ?? [0, 0, 0, 0]
    // We don't care about alpha
    components.removeLast()
    
    let byteArray: [UInt8] = components.map({ UInt8($0 * 255) })
    return Data(byteArray)
  }
}

class AnimatedRainbowMode: LEDMode, ObservableObject {
  var rainbowLength: UInt16 = 64
  var cycleTimeSeconds: Double = 1.0
  
  private var cycleTime_ms: UInt32 {
    UInt32(self.cycleTimeSeconds * 1000)
  }
  
  var id: UInt8 = 0x02
  var data: Data {
    var data: Data = rainbowLength.data
    data.append(cycleTime_ms.data)
    
    return data
  }
}
