#pragma once

#include "Schedule.h"

typedef enum
{
    OFF = 0,
    FIRST = 1,
    LAST = 2,
    ALL = FIRST | LAST
} DisplayFlags;

class GranularSchedule : public Schedule<DisplayFlags>
{
public:
    GranularSchedule(DisplayFlags defaultValue, byte identifier);

    // virtual DisplayFlags valueFor(byte hour);
    bool valueFor(byte hour, byte minute);
};