#ifndef Component_h
#define Component_h

#include "common.h"

class Component
{
public:
    Component();

    virtual void setLed(byte led, bool show) = 0;
    virtual bool led(byte) = 0;

    virtual void clear() = 0;
};

#endif