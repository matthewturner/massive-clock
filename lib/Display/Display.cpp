#include "Display.h"

Display::Display()
{
}

bool Display::led(byte led)
{
  return componentFor(led)->led(offset(led));
}

Component *Display::componentFor(byte led)
{
  byte remaining = led;
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    if (remaining < _components[i]->ledCount())
    {
      return _components[i];
    }
    remaining -= _components[i]->ledCount();
  }
  return nullptr;
}

byte Display::offset(byte led)
{
  byte remaining = led;
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    if (remaining < _components[i]->ledCount())
    {
      return remaining;
    }
    remaining -= _components[i]->ledCount();
  }
  return remaining;
}

void Display::setLed(byte led, bool show)
{
  componentFor(led)->setLed(offset(led), show);
}

void Display::clear()
{
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    _components[i]->clear();
  }
}

void Display::setDigit(byte digit, byte value)
{
  _components[digit]->set(value);
}

void Display::setDots(byte digit, byte value)
{
  _components[digit]->setDots(value);
}

void Display::setPart(byte part, byte value, Flags flags)
{
  byte offset = part * 2;
  if (offset > 0)
  {
    offset++;
  }
  byte tens = (value - (value % 10)) / 10;
  byte unit = value % 10;
  bool minimalMode = ((flags & Flags::MINIMAL) == Flags::MINIMAL);
  if (minimalMode)
  {
    setDots(0 + offset, 0);
  }
  else
  {
    setDigit(0 + offset, unit);
  }
  bool leadingZero = ((flags & Flags::LEADING_ZERO) == Flags::LEADING_ZERO);
  if (leadingZero || tens > 0)
  {
    if (minimalMode)
    {
      setDots(1 + offset, tens);
    }
    else
    {
      setDigit(1 + offset, tens);
    }
  }
  setSeparator((flags & Flags::SEPARATOR) == Flags::SEPARATOR);
}

void Display::setText(const char *text)
{
  setDigit(4, text[0]);
  setDigit(3, text[1]);
  setDigit(1, text[2]);
  setDigit(0, text[3]);
}

void Display::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    componentFor(i)->setLed(offset(i), show);
  }
}

bool Display::updateFrom(Display *other)
{
  bool updated = false;
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (led(i) != other->led(i))
    {
      setLed(i, other->led(i));
      updated = true;
    }
  }
  if (_brightness != other->_brightness)
  {
    _brightness = other->_brightness;
    updated = true;
  }
  if (_color != other->_color)
  {
    _color = other->_color;
    updated = true;
  }
  return updated;
}

void Display::setSeparator(bool show)
{
  _separator.setAll(show);
}

void Display::setBrightness(byte value)
{
  _brightness = value;
}

byte Display::getBrightness()
{
  return _brightness;
}

void Display::setColor(long value)
{
  _color = value;
}

long Display::getColor()
{
  return _color;
}