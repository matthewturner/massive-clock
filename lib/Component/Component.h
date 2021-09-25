#ifndef Component_h
#define Component_h

#include "common.h"

class Component
{
public:
    Component();

    virtual void set(byte value) = 0;
    virtual void setLed(byte led, bool show) = 0;
    virtual bool led(byte) = 0;
    virtual void setDots(byte count) = 0;

    virtual void clear() = 0;

    virtual byte ledCount() = 0;
};

#endif