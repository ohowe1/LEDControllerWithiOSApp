#pragma once

#include "LEDAnimation.h"

using namespace led;

class AnimatedRainbowAnimation : public LEDAnimation {
public:
    AnimatedRainbowAnimation(unsigned int sizeOfRainbow, unsigned long timeForFullCycleMs, CRGB *leds,
                             unsigned int amountOfLeds) : LEDAnimation(leds, amountOfLeds),
                                                          sizeOfRainbow(sizeOfRainbow),
                                                          loopTime(timeForFullCycleMs / 255) {

    }

    void loop() override {
        unsigned long currentMillis = millis();
        if (currentMillis - lastMillis >= loopTime) {
            lastMillis = currentMillis;

            createRainbow(currentUnit, sizeOfRainbow, leds, amountOfLeds);
            FastLED.show();

            if (currentUnit == 255) {
                currentUnit = 0;
            } else {
                currentUnit++;
            }
        }

    }

protected:
    unsigned int sizeOfRainbow;
    unsigned long loopTime;
    uint8_t currentUnit = 0;

    unsigned long lastMillis = 0;
};
