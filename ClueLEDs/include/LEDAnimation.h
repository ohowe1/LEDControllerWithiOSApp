#pragma once

#include "FastLED.h"

namespace led {

    class LEDAnimation {
    public:
        virtual void setup() {}

        virtual void loop() {}

        LEDAnimation(CRGB *leds, unsigned int amountOfLeds) {
            this->leds = leds;
            this->amountOfLeds = amountOfLeds;
        }

        static void createRainbow(uint8_t startingAngle, uint8_t rainbowLength, CRGB *dest, unsigned int size) {
            const uint16_t unitsPerLed = 256 / rainbowLength;
            uint8_t nextUnit = startingAngle;
            for (unsigned int i = 0; i < size; i++) {
                CHSV hsv = CHSV(nextUnit, 255, 255);
                hsv2rgb_rainbow(hsv, dest[i]);
                nextUnit += unitsPerLed;

                // Reached the maximum
                if (nextUnit >= 255) {
                    nextUnit = 0;
                }
            }
        }

        static void setAll(CRGB color, CRGB *dest, unsigned int size) {
            for (unsigned int i = 0; i < size; i++) {
                dest[i] = color;
            }
        }

    protected:
        CRGB *leds;
        unsigned int amountOfLeds;

        void set(int index, CRGB color) {
            leds[index] = color;
        }
    };
}