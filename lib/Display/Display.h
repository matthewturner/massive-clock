#ifndef Digit_h
#define Digit_h

#include <stdint.h>
typedef uint8_t byte;

#define NUM_LEDS 60
const byte LEDS_PER_SEGMENT = 2;
const byte SEGMENTS_PER_DIGIT = 7;
const byte LEDS_IN_SEPARATOR = 2;
const byte LEDS_PER_DIGIT = LEDS_PER_SEGMENT * SEGMENTS_PER_DIGIT;

const byte SEG_TOP_LEFT = 0;
const byte SEG_TOP = 1;
const byte SEG_TOP_RIGHT = 2;
const byte SEG_MIDDLE = 3;
const byte SEG_BOTTOM_LEFT = 4;
const byte SEG_BOTTOM = 5;
const byte SEG_BOTTOM_RIGHT = 6;

class Display
{
public:
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value);
    void bufferDigit(byte value);
    void applyDigit(byte digit);
    void bufferSegment(byte segment, bool show);
    void bufferAllSegments(bool show);
    void setSegmentRange(byte first, byte last, bool show);
    void setLedRange(byte first, byte last, bool show);
    void clear();

private:
    bool _segments[SEGMENTS_PER_DIGIT];
    bool _leds[NUM_LEDS];
};

#endif