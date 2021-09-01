#include "Separator.h"

bool Separator::led(byte led)
{
  return _leds[led];
}

void Separator::setAll(bool show)
{
  for (byte i = 0; i < LEDS_IN_SEPARATOR; i++)
  {
    setLed(i, show);
  }
}

void Separator::clear()
{
  setAll(false);
}

void Separator::show()
{
  setAll(true);
}

void Separator::hide()
{
  setAll(false);
}

void Separator::set(byte value)
{
}

void Separator::setLed(byte led, bool show)
{
  _leds[led] = show;
}

void Separator::setRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    setLed(i, show);
  }
}