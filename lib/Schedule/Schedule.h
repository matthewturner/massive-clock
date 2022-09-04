#ifndef Schedule_h
#define Schedule_h

#include "common.h"

const byte HOURS_IN_DAY = 24;
const byte SEGMENTS_IN_HOUR = 6;
const byte SEGMENTS_IN_DAY = HOURS_IN_DAY * SEGMENTS_IN_HOUR;
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
        for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
        {
            _values[i] = _defaultValue;
        }
    }

    T valueForHour(byte hour)
    {
        return _values[hour * SEGMENTS_IN_HOUR];
    }

    T valueForMinuteSinceMidnight(byte minutes)
    {
        return _values[minutes];
    }

    void setupHours(byte min, byte max, T value)
    {
        for (byte i = min; i <= max; i++)
        {
            _values[i] = value;
        }
    }

private:
    T _defaultValue;
    T _values[SEGMENTS_IN_DAY];
};

#endif