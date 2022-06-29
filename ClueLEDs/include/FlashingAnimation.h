#pragma once

#include "LEDAnimation.h"

using namespace led;

class FlashingAnimation : public LEDAnimation {
public:
    FlashingAnimation(CRGB color1, CRGB color2, unsigned long loopTimeMs, CRGB *leds, unsigned int amountOfLeds) : LEDAnimation(leds, amountOfLeds),
                                                                             color1(color1), color2(color2), loopTimeMs(loopTimeMs) {}

    void loop() override {
        unsigned long currentMillis = millis();
        if (currentMillis - lastMillis >= loopTimeMs) {
            if (!onColor1) {
                setAll(color1, leds, amountOfLeds);
            } else {
                setAll(color2, leds, amountOfLeds);
            }
            FastLED.show();
            onColor1 = !onColor1;
            lastMillis = currentMillis;
        }
    }

protected:
    CRGB color1;
    CRGB color2;
    unsigned long loopTimeMs;
    unsigned long lastMillis = 0;
    bool onColor1 = false;
};
