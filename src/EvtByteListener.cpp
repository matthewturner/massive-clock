#include "EvtByteListener.h"

EvtByteListener::EvtByteListener(byte targetValue, char triggerMode, EvtAction action)
{
    _targetValue = targetValue;
    _lastValue = targetValue + 1;
    triggerAction = action;
    triggerMode = triggerMode;
}

EvtByteListener::EvtByteListener(byte targetValue, EvtAction action)
    : EvtByteListener(targetValue, ON_CHANGE, triggerAction)
{
}

void EvtByteListener::setupListener()
{
    _lastValue = _targetValue + 99;
}

bool EvtByteListener::isEventTriggered()
{
    volatile byte lastValue = _lastValue;
    _lastValue = value;

    if (!EvtListener::isEventTriggered())
    {
        return false;
    }

    if (value != _targetValue)
    {
        return false;
    }

    if (triggerMode == ON_CHANGE && value == lastValue)
    {
        return false;
    }

    return true;
}