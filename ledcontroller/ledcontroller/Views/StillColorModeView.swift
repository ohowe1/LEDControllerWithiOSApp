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
    HStack {
      ColorPicker(selection: $modeState.color, supportsOpacity: false) {
        Text("LED Color")
      }
      .frame(maxWidth: 150)
    }
  }
}

struct StillColorView_Previews: PreviewProvider {
  static var previews: some View {
    StillColorModeView(modeState: StillColorMode())
  }
}
