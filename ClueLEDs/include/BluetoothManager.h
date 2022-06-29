#pragma once

#include <bluefruit.h>

class BluetoothManager {
public:
    explicit BluetoothManager(void (*modeCallback)(uint16_t, BLECharacteristic *, uint8_t *, uint16_t)): modeCallback(modeCallback) {}

    void setup();
private:
    static uint8_t char2int(char input) {
        if(input >= '0' && input <= '9')
            return input - '0';
        if(input >= 'A' && input <= 'F')
            return input - 'A' + 10;
        if(input >= 'a' && input <= 'f')
            return input - 'a' + 10;
        return 0;
    }
    static BLEUuid uuidFromString(const char* str) {
        // assumes no dashes
        uint8_t bytes[16];
        for (int i = 0; i + 1 < 32; i+=2) {
            bytes[i] = char2int(str[i]) * 16 + char2int(str[i + 1]);
        }

        return {bytes};
    }
    BLEService ledService = BLEService("96cf1825-f046-4266-8a68-14c04101c9b7");
    BLECharacteristic modeCharacteristic = BLECharacteristic("398453f9-14a3-4412-908c-aedfebb4608c");
    BLEDis bleDis;

    BLECharacteristic::write_cb_t modeCallback;
};
