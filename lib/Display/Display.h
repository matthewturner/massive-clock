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
const byte SEG_TOP = SEG_TOP_LEFT + LEDS_PER_SEGMENT;
const byte SEG_TOP_RIGHT = SEG_TOP + LEDS_PER_SEGMENT;
const byte SEG_MIDDLE = SEG_TOP_RIGHT + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM_LEFT = SEG_MIDDLE + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM = SEG_BOTTOM_LEFT + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM_RIGHT = SEG_BOTTOM + LEDS_PER_SEGMENT;

class Display
{
public:
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value);
    void bufferDigit(byte value);
    void applyDigit(byte digit);
    void setSegment(byte segment, bool show);
    void showSegment(byte segment);
    void hideSegment(byte segment);
    void showAllSegments();

private:
    bool _segments[LEDS_PER_DIGIT];
    bool _leds[NUM_LEDS];
};

#endif