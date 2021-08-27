#ifndef Separator_h
#define Separator_h

#include "common.h"

const byte LEDS_IN_SEPARATOR = 2;

class Separator
{
public:
    bool led(byte led);
    void set(byte led, bool show);
    void setRange(byte first, byte last, bool show);
    void show();
    void hide();
    void clear();
    void setAll(bool show);

private:
    bool _leds[LEDS_IN_SEPARATOR];
};

#endif