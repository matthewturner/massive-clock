#ifndef Display_h
#define Display_h

#include "common.h"
#include "Digit.h"
#include "Separator.h"

const byte NUM_LEDS = 42;
const byte NUM_DIGITS = 2;

class Display
{
public:
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value, bool leadingZero);
    void setLed(byte led, bool show);
    void setLedRange(byte first, byte last, bool show);
    void clear();
    void setAll();
    void hide();
    void show();
    void setSeparator(bool show);
    bool updateFrom(Display *other);

private:
    Digit _digits[NUM_DIGITS];
    Separator _separator;

    Component *componentFor(byte led);
    byte offset(byte led);
};

#endif