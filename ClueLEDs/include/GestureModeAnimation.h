#pragma once

#include "LEDAnimation.h"
#include <Arduino_APDS9960.h>

using namespace led;

class GestureModeAnimation : public LEDAnimation {
public:
    GestureModeAnimation(CRGB *leds, unsigned int amountOfLeds) : LEDAnimation(leds, amountOfLeds) {}

    void setup() override {
        pinMode(43, OUTPUT);
        digitalWrite(43, LOW);
        APDS.begin();
    }

    void loop() override {
        if (currentState == lookingForColor) {
            if (APDS.colorAvailable()) {
                int r, g, b, a;
                APDS.readColor(r, g, b, a);
                setAll({(uint8_t) r, (uint8_t) g, (uint8_t) b}, leds, amountOfLeds);
                FastLED.show();
            }
        } else {
            if (APDS.gestureAvailable()) {
                int gesture = APDS.readGesture();
                Serial.println(gesture);
                switch (gesture) {
                    case GESTURE_LEFT:
                        if (currentState != lookingForColor) {
                            currentRainbow -= 25;
                            setAll(CHSV(currentRainbow, 255, 255), leds, amountOfLeds);
                            FastLED.show();
                        }
                        break;
                    case GESTURE_RIGHT:
                        if (currentState != lookingForColor) {
                            currentRainbow += 25;
                            setAll(CHSV(currentRainbow, 255, 255), leds, amountOfLeds);
                            FastLED.show();
                        }
                        break;
                    case GESTURE_UP:
                        currentState = lookingForColor;
                        digitalWrite(43, HIGH);
                        break;
                    case GESTURE_DOWN:
                        currentState = locked;
                        digitalWrite(43, LOW);
                        break;
                    default:
                        break;
                }
            }
        }
    }
protected:
    enum state {
        lookingForColor,
        locked
    };
    state currentState = locked;
    uint8_t currentRainbow = 0;
};
