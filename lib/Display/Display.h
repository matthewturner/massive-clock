#ifndef Display_h
#define Display_h

#include "common.h"
#include "Component.h"
#include "Digit.h"
#include "Separator.h"
#include <Arduino.h>

const byte NUM_LEDS = 86;
const byte NUM_COMPONENTS = 5;

typedef enum
{
    NONE = 0,
    SEPARATOR = 1,
    MINIMAL = 2,
    BRIGHT = 4,
    LEADING_ZERO = 8,
    STANDARD = SEPARATOR
} Flags;

class Display
{
public:
    Display();
    bool led(byte led);
    void setDigit(byte digit, byte value);
    void setPart(byte part, byte value, Flags flags);
    void setDots(byte digit, byte value);
    void setLed(byte led, bool show);
    void setLedRange(byte first, byte last, bool show);
    void setText(const char *text);
    void setText(const __FlashStringHelper *text);
    void setBrightness(byte value);
    void setColor(long color);
    byte getBrightness();
    long getColor();
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

    byte _brightness = 5;
    long _color;

    Component *componentFor(byte led);
    byte offset(byte led);
};

#endif