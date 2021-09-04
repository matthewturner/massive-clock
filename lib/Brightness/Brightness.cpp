#include "Brightness.h"

byte Brightness::from(byte value)
{
    // byte newValue = map(value, 0, 400, 40, 0);
    // newValue = (byte)(((newValue + _previous) / 2) + 0.5);
    // _previous = newValue;
    // return _previous;
    return value;
}

void Brightness::reset()
{
    _previous = 0;
}