#pragma once
#include "common.h"

const byte BLOCKS_PER_HOUR = 4;
const byte HOURS_IN_DAY = 24;
const byte BLOCKS = HOURS_IN_DAY * BLOCKS_PER_HOUR;
const byte WINTER_SCHEDULE = 1;
const byte SUMMER_SCHEDULE = 0;

typedef enum
{
    BNONE = 0,
    FIRST = 1,
    SECOND = 2,
    THIRD = 4,
    LAST = 8,
    FIRST_HALF = FIRST | SECOND,
    SECOND_HALF = THIRD | LAST,
    ALL = FIRST_HALF | SECOND_HALF
} BlockFlags;

template <class T>
class Schedule
{
public:
    Schedule(T defaultValue)
    {
        _defaultValue = defaultValue;
        _identifier = 99;
        reset();
    }

    Schedule(T defaultValue, byte identifier)
    {
        _defaultValue = defaultValue;
        _identifier = identifier;
        reset();
    }

    void reset()
    {
        for (byte i = 0; i < BLOCKS; i++)
        {
            _valuesForHour[i] = _defaultValue;
        }
    }

    T valueFor(byte hour)
    {
        return valueFor(hour, 0);
    }

    T valueFor(byte hour, byte minute)
    {
        byte block = 0;
        if (minute < 15)
        {
            block = 0;
        }
        else if (minute < 30)
        {
            block = 1;
        }
        else if (minute < 45)
        {
            block = 2;
        }
        else
        {
            block = 3;
        }

        return _valuesForHour[(hour * BLOCKS_PER_HOUR) + block];
    }

    void setup(byte min, byte max, T value)
    {
        for (byte i = min * BLOCKS_PER_HOUR; i < (max + 1) * BLOCKS_PER_HOUR; i++)
        {
            _valuesForHour[i] = value;
        }
    }

    bool update(uint32_t encodedSchedule)
    {
        uint32_t tempEncodedSchedule = encodedSchedule;

        uint32_t value = tempEncodedSchedule % 10;
        tempEncodedSchedule /= 10;

        BlockFlags bFlags = BlockFlags::ALL;
        if ((uint32_t)(encodedSchedule / 10000) > 0)
        {
            // long format
            uint32_t flagValue = tempEncodedSchedule % 100;

            if (flagValue > 63)
            {
                return false;
            }

            bFlags = (BlockFlags)flagValue;

            tempEncodedSchedule /= 100;
        }

        uint32_t hour = tempEncodedSchedule % 100;
        if (hour > 23)
        {
            return false;
        }
        tempEncodedSchedule /= 100;
        uint32_t identifier = tempEncodedSchedule;

        if (identifier != _identifier)
        {
            return false;
        }

        if ((bFlags & BlockFlags::FIRST) == BlockFlags::FIRST)
        {
            _valuesForHour[hour * BLOCKS_PER_HOUR] = (T)value;
        }
        if ((bFlags & BlockFlags::SECOND) == BlockFlags::SECOND)
        {
            _valuesForHour[(hour * BLOCKS_PER_HOUR) + 1] = (T)value;
        }
        if ((bFlags & BlockFlags::THIRD) == BlockFlags::THIRD)
        {
            _valuesForHour[(hour * BLOCKS_PER_HOUR) + 2] = (T)value;
        }
        if ((bFlags & BlockFlags::LAST) == BlockFlags::LAST)
        {
            _valuesForHour[(hour * BLOCKS_PER_HOUR) + 3] = (T)value;
        }

        return true;
    }

private:
    T _defaultValue;
    T _valuesForHour[BLOCKS];
    byte _identifier;
};