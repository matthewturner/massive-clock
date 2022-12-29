#pragma once

#include "common.h"

const byte BLOCKS_PER_HOUR = 4;
const byte HOURS_IN_DAY = 24;
const byte BLOCKS = HOURS_IN_DAY * BLOCKS_PER_HOUR;

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
        for (byte h = 0; h < HOURS_IN_DAY; h++)
        {
            setValueFor(h, BlockFlags::ALL, _defaultValue);
        }
    }

    T valueFor(byte hour)
    {
        return valueFor(hour, 0);
    }

    T valueFor(byte hour, byte minute)
    {
        byte block = minute / (60 / BLOCKS_PER_HOUR);

        return _valuesForBlock[indexFor(hour, block)];
    }

    void setup(byte min, byte max, T value)
    {
        for (byte h = min; h <= max; h++)
        {
            setValueFor(h, BlockFlags::ALL, value);
        }
    }

    void setValueFor(byte hour, BlockFlags flags, T value)
    {
        for (byte b = 0; b < BLOCKS_PER_HOUR; b++)
        {
            byte flag = flags >> b;
            if ((flag & 1) == 1)
            {
                _valuesForBlock[indexFor(hour, b)] = value;
            }
        }
    }

    bool update(uint32_t encodedSchedule)
    {
        uint32_t tempEncodedSchedule = encodedSchedule;

        uint32_t value = tempEncodedSchedule % 10;
        tempEncodedSchedule /= 10;

        uint32_t flagValue = BlockFlags::ALL;
        if ((uint32_t)(encodedSchedule / 10000) > 0)
        {
            // long format
            flagValue = tempEncodedSchedule % 100;

            if (flagValue > BlockFlags::ALL)
            {
                return false;
            }

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

        setValueFor(hour, (BlockFlags)flagValue, (T)value);

        return true;
    }

private:
    T _defaultValue;
    T _valuesForBlock[BLOCKS];
    byte _identifier;

    byte indexFor(byte hour, byte block)
    {
        return (hour * BLOCKS_PER_HOUR) + block;
    }
};