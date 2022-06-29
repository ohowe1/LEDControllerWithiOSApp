#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include <PDM.h>
#include "FastLED.h"
#include "Animations.h"

#define BLUETOOTH
#ifdef BLUETOOTH
#include "BluetoothManager.h"
#endif

using namespace led;
_FL_DEFPIN(1, 5, 0);

const unsigned int amountOfLeds = 16;

CRGB leds[amountOfLeds];

LEDAnimation* animation = new AnimatedRainbowAnimation(64, 60 * 1000, leds, amountOfLeds);
//LEDAnimation* animation = new GestureModeAnimation(leds, amountOfLeds);

uint8_t currentMode = 0x01;

bool createStillColor(const uint8_t* data, uint16_t length) {
    if (length < 3) {
        return false;
    }
    CRGB color = { data[0], data[1], data[2] };

    animation = new StillColorAnimation(color, leds, amountOfLeds);
    return true;
}

bool createAnimatedRainbow(const uint8_t* data, uint16_t length) {
    if (length < 6) {
        return false;
    }

    uint16_t sizeOfRainbow = data[0] | data[1] << 8;
    uint32_t timeForFullCycle = data[2] | data[3] << 8 | data[4] << 16 | data[5] << 24;

    animation = new AnimatedRainbowAnimation(sizeOfRainbow, timeForFullCycle, leds, amountOfLeds);

    return true;
}

#ifdef BLUETOOTH
void modeCallBack(uint16_t connectionHandle, BLECharacteristic* characteristic, uint8_t* data, uint16_t length) {
    uint8_t mode = data[0];
    uint8_t* modeSettingsData = data + 1;
    uint16_t modeSettingsLength = length - 1;

    bool goodData;
    switch (mode) {
        case 0x01: {
            goodData = createStillColor(modeSettingsData, modeSettingsLength);
            break;
        }
        case 0x02: {
            goodData = createAnimatedRainbow(modeSettingsData, modeSettingsLength);
            break;
        }

        default:
            goodData = false;
    }

    if (goodData) {
        currentMode = mode;
        animation->setup();
    }
}

BluetoothManager* bluetoothManager = new BluetoothManager(modeCallBack);
#endif

void setup() {
    Serial.begin(42069);
    FastLED.addLeds<WS2812, 1, BRG>(leds, amountOfLeds);
    FastLED.setCorrection(TypicalSMD5050);

#ifdef BLUETOOTH
    bluetoothManager->setup();
#endif
    animation->setup();
}

void loop() {
    animation->loop();
}
#pragma clang diagnostic pop
