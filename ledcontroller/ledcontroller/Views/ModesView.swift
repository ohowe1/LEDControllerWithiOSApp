//
//  ModesView.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/29/22.
//

import SwiftUI

struct ModesView: View {
  @EnvironmentObject var bleManager: BLEManager;
  @State var ledMode: LEDMode = AnimatedRainbowMode()
  var body: some View {
    VStack {
      if ledMode is StillColorMode {
        StillColorModeView(modeState: ledMode as! StillColorMode)
        Button(action: { ledMode = AnimatedRainbowMode() }) {
          Text("Switch to Animated Rainbow Mode")
        }
      } else if ledMode is AnimatedRainbowMode {
        AnimatedRainbowModeView(modeState: ledMode as! AnimatedRainbowMode)
        Button(action: { ledMode = StillColorMode() }) {
          Text("Switch to Still Color Mode")
        }
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
    }
  }
}

struct ModesView_Previews: PreviewProvider {
  static var previews: some View {
    ModesView()
      .environmentObject(BLEManager())
  }
}
