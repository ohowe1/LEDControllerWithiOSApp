//
//  LEDControllerApp.swift
//  LEDController
//
//  Created by Oliver Howe on 6/27/22.
//

import SwiftUI

@main
struct LEDControllerApp: App {
  @ObservedObject var bleManager: BLEManager = BLEManager()
  var body: some Scene {
    WindowGroup {
      ContentView()
        .environmentObject(bleManager)
    }
  }
}
