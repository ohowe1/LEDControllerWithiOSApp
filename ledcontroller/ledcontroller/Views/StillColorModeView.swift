//
//  StillColorView.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/27/22.
//

import SwiftUI

struct StillColorModeView: View {
  @ObservedObject var modeState: StillColorMode
  var body: some View {
    Form {
      Section(header: Text("Color")) {
      ColorPicker(selection: $modeState.color, supportsOpacity: false) {
      }
      .labelsHidden()
      }
    }
  }
}

struct StillColorView_Previews: PreviewProvider {
  static var previews: some View {
    StillColorModeView(modeState: StillColorMode())
      .environmentObject(BLEManager())
  }
}
