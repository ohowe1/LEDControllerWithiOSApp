#pragma once

#include "LEDAnimation.h"

using namespace led;

class StillColorAnimation : public LEDAnimation {
public:
    StillColorAnimation(CRGB color, CRGB *leds, unsigned int amountOfLeds) : LEDAnimation(leds, amountOfLeds),
                                                                             color(color) {}

    void setup() override {
        setAll(color, leds, amountOfLeds);
        FastLED.show();
    }

protected:
    CRGB color;
};
