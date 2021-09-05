#ifndef Display_h
#define Display_h

#include "common.h"
#include "Component.h"
#include "Digit.h"
#include "Separator.h"

const byte NUM_LEDS = 86;
const byte NUM_COMPONENTS = 5;

class Display
{
public:
    Display();
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value, bool leadingZero);
    void setLed(byte led, bool show);
    void setLedRange(byte first, byte last, bool show);
    void clear();
    void setAll();
    void setSeparator(bool show);
    bool updateFrom(Display *other);

private:
    Component *_components[NUM_COMPONENTS] = {&_digit0, &_digit1, &_separator, &_digit2, &_digit3};
    Digit _digit0;
    Digit _digit1;
    Separator _separator;
    Digit _digit2;
    Digit _digit3;

    Component *componentFor(byte led);
    byte offset(byte led);
};

#endif