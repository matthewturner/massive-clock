#ifndef Digit_h
#define Digit_h

#include "common.h"
#include "Component.h"

const byte LEDS_PER_SEGMENT = 3;
const byte SEGMENTS_PER_DIGIT = 7;
const byte LEDS_PER_DIGIT = LEDS_PER_SEGMENT * SEGMENTS_PER_DIGIT;

const byte SEG_TOP_LEFT = 2;
const byte SEG_TOP = 1;
const byte SEG_TOP_RIGHT = 0;
const byte SEG_MIDDLE = 3;
const byte SEG_BOTTOM_LEFT = 6;
const byte SEG_BOTTOM = 5;
const byte SEG_BOTTOM_RIGHT = 4;

class Digit : public Component
{
public:
    bool led(byte led) override;
    void set(byte value);
    void setSegment(byte segment, bool show);
    void setAll(bool show);
    void setSegmentRange(byte first, byte last, bool show);
    void setLedRange(byte first, byte last, bool show);
    void setLed(byte led, bool show) override;
    void clear() override;
    byte ledCount() override;

private:
    bool _leds[LEDS_PER_DIGIT];
};

#endif