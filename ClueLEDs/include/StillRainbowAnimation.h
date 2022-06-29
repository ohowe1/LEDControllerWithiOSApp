#pragma once

#include "LEDAnimation.h"

using namespace led;

class StillRainbowAnimation : public LEDAnimation {
public:
    StillRainbowAnimation(unsigned int sizeOfRainbow, CRGB *leds, unsigned int amountOfLeds) : LEDAnimation(leds,
                                                                                                            amountOfLeds),
                                                                                               sizeOfRainbow(
                                                                                                       sizeOfRainbow) {}

    void setup() override {
        createRainbow(0, sizeOfRainbow, leds, amountOfLeds);
        FastLED.show();
    }

protected:
    unsigned int sizeOfRainbow;
};
