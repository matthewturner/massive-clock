#ifndef Schedule_h
#define Schedule_h

#include "common.h"

const byte HOURS_IN_DAY = 24;
const byte WINTER_SCHEDULE = 1;
const byte SUMMER_SCHEDULE = 0;

template <class T>
class Schedule
{
public:
    Schedule(T defaultValue)
    {
        _defaultValue = defaultValue;
        reset();
    }

    void reset()
    {
        for (byte i = 0; i < HOURS_IN_DAY; i++)
        {
            _valuesForHour[i] = _defaultValue;
        }
    }

    T valueFor(byte hour)
    {
        return _valuesForHour[hour];
    }

    void setup(byte min, byte max, T value)
    {
        for (byte i = min; i <= max; i++)
        {
            _valuesForHour[i] = value;
        }
    }

private:
    T _defaultValue;
    T _valuesForHour[HOURS_IN_DAY];
};

#endif