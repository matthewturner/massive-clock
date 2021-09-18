#ifndef EvtByteListener_h
#define EvtByteListener_h

#include <EvtListener.h>
#include <EvtIntegerListener.h>
#include <Arduino.h>

class EvtByteListener : public EvtListener
{
public:
    EvtByteListener(byte targetValue, EvtAction action);
    EvtByteListener(byte targetValue, char triggerMode, EvtAction action);
    void setupListener();
    bool isEventTriggered();
    char triggerMode = ON_CHANGE;
    volatile byte value = 0;

private:
    byte _targetValue;
    volatile byte _lastValue = 0;
};

#endif