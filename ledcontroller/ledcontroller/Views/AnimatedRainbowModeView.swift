//
//  AnimatedRainbowModeView.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/28/22.
//

import SwiftUI

struct AnimatedRainbowModeView: View {
  enum Field: Hashable {
    case length
    case time
  }
  
  @ObservedObject var modeState: AnimatedRainbowMode
  let lengthFormatter: NumberFormatter = {
    let formatter = NumberFormatter()
    formatter.numberStyle = .decimal
    formatter.minimum = NSNumber(value: UInt16.min)
    formatter.maximum = NSNumber(value: UInt16.max)
    formatter.allowsFloats = false
    
    return formatter
  }()
  
  let timeFormatter: NumberFormatter = {
    let formatter = NumberFormatter()
    formatter.numberStyle = .decimal
    formatter.minimum = NSNumber(value: UInt32.min / 1000)
    formatter.maximum = NSNumber(value: UInt32.max / 1000)
    
    return formatter
  }()
  
  var body: some View {
    Form {
      Section(header: Text("Length of full rainbow")) {
        TextField("In LEDs", value: $modeState.rainbowLength, formatter: lengthFormatter)
          .keyboardType(.numberPad)
      }
      Section(header: Text("Seconds for a full color cycle")) {
        TextField("In seconds", value: $modeState.cycleTimeSeconds, formatter: timeFormatter)
          .keyboardType(.decimalPad)
      }
    }
  }
}

struct AnimatedRainbowModeView_Previews: PreviewProvider {
  static var previews: some View {
    AnimatedRainbowModeView(modeState: AnimatedRainbowMode())
  }
}
