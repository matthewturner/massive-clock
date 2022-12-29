#include "GranularSchedule.h"

GranularSchedule::GranularSchedule(DisplayFlags defaultValue, byte identifier)
    : Schedule(defaultValue, identifier)
{
}

bool GranularSchedule::valueFor(byte hour, byte minute)
{
    DisplayFlags setting = Schedule::valueFor(hour);
    if (minute < 30 && (setting & DisplayFlags::FIRST) == DisplayFlags::FIRST)
    {
        return true;
    }
    if (minute >= 30 && (setting & DisplayFlags::LAST) == DisplayFlags::LAST)
    {
        return true;
    }
    return false;
}