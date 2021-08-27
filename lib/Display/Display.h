#ifndef Display_h
#define Display_h

#include "common.h"
#include "Digit.h"
#include "Separator.h"

#define NUM_LEDS 60
const byte NUM_DIGITS = 4;

class Display
{
public:
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value);
    void setLed(byte led, bool show);
    void setLedRange(byte first, byte last, bool show);
    void clear();
    void setAll();
    void hide();
    void show();

private:
    Digit _digits[NUM_DIGITS];
    Separator _separator;

    Digit *digitFor(byte led);
    byte offset(byte led);
};

#endif