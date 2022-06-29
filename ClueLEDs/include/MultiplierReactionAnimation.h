#pragma once

#include "LEDAnimation.h"

using namespace led;
typedef float (*func)();

class MultiplierReactionAnimation : public LEDAnimation {
public:
    MultiplierReactionAnimation(CRGB fullColor, func valueSupplier, CRGB *leds, unsigned int amountOfLeds) : LEDAnimation(leds, amountOfLeds), fullColor(fullColor), supplier(valueSupplier) {}

    void loop() override {
        float supplierValue = supplier();
        uint8_t divider = 0;
        if (supplierValue != 0) {
            divider = (uint8_t) (1.0 / supplierValue);
        }
        CRGB newColor = fullColor;
        if (divider != 0) {
            newColor /= divider;
        } else {
            newColor *= 0;
        }
        setAll(newColor, leds, amountOfLeds);
        FastLED.show();
    }

protected:
    CRGB fullColor;
    func supplier;
};
