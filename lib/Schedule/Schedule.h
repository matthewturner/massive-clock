#ifndef Schedule_h
#define Schedule_h

#include "common.h"

const byte HOURS_IN_DAY = 24;
const byte SEGMENTS_IN_HOUR = 6;
const byte SEGMENTS_IN_DAY = HOURS_IN_DAY * SEGMENTS_IN_HOUR;
const byte MINUTES_IN_SEGMENT = 60 / SEGMENTS_IN_HOUR;
const byte WINTER_SCHEDULE = 1;
const byte SUMMER_SCHEDULE = 0;
const byte GRANULARITY_HOUR = 0;
const byte GRANULARITY_SEGMENT = 1;

template <class T>
class Schedule
{
public:
    Schedule(T defaultValue)
    {
        _defaultValue = defaultValue;
        _granularity = GRANULARITY_HOUR;
        reset();
    }

    Schedule(T defaultValue, byte granularity)
    {
        _defaultValue = defaultValue;
        _granularity = granularity;
        reset();
    }

    void reset()
    {
        for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
        {
            _values[i] = _defaultValue;
        }
    }

    T valueFor(byte hoursOrMinutes)
    {
        if (_granularity == GRANULARITY_HOUR)
        {
            return _values[hoursOrMinutes];
        }

        byte minutesSinceMidnight = hoursOrMinutes - (hoursOrMinutes % MINUTES_IN_SEGMENT);
        return _values[minutesSinceMidnight];
    }

    void setup(byte min, byte max, T value)
    {
        for (byte i = min; i <= max; i++)
        {
            _values[i] = value;
        }
    }

private:
    T _defaultValue;
    byte _granularity;
    T _values[SEGMENTS_IN_DAY];
};

#endif