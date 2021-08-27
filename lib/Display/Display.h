#ifndef Digit_h
#define Digit_h

#include "common.h"
#include "Digit.h"
#include "Separator.h"

#define NUM_LEDS 60

class Display
{
public:
    bool led(byte led);
    void setDigit(byte digit, byte value);
    // void setPart(byte part, byte value);
    // void setSegment(byte segment, bool show);
    // void setSegmentRange(byte first, byte last, bool show);
    // void setLedRange(byte first, byte last, bool show);
    void clear();
    void setAll();
    void hide();
    void show();

private:
    Digit _digits[4];
    Separator _separator;
};

#endif