//
//  ContentView.swift
//  ledcontroller
//
//  Created by Oliver Howe on 6/27/22.
//

import SwiftUI

struct ContentView: View {
  @EnvironmentObject var bleManager: BLEManager
  
  var body: some View {
    VStack {
      if bleManager.isConnected {
        ModesView()
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
