#ifndef Brightness_h
#define Brightness_h

#include "common.h"

class Brightness
{
public:
    byte from(byte value);
    void reset();

private:
    byte _previous;
};

#endif