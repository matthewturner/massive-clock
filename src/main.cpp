#include "main.h"

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(10);

  while (!Serial)
    ;

  if (!clock.begin())
  {
    Serial.println("Couldn't find Realtime Clock");
    Serial.flush();
    abort();
  }

  if (clock.lostPower())
  {
    Serial.println("Realtime Clock lost power, setting the time...");
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.println("Populating colors...");
  populateColorCodes();

  Serial.println("Testing display 88...");
  display.setPart(0, 88, false);
  delay(500);

  mgr.addListener(new EvtTimeListener(500, true, (EvtAction)showTime));

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  mgr.loopIteration();
}

bool showTime()
{
  now = clock.now();
  byte hour = now.hour();
  byte minute = now.minute();

  if (showing <= 2)
  {
    display.setPart(0, hour, false);
    showing++;
  }
  else if (showing <= 4)
  {
    display.setPart(0, minute, true);
    showing++;
  }
  else
  {
    display.clear();
    showing = 0;
  }
  showDigits();

  return false;
}

void showDigits()
{
  CRGB::HTMLColorCode colorCode = determineColorCode();

  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (display.led(i))
    {
      physicalLeds[i] = colorCode;
    }
    else
    {
      physicalLeds[i] = CRGB::Black;
    }
  }

  FastLED.show();
}

CRGB::HTMLColorCode determineColorCode()
{
  byte hour = now.hour();
  return colorCodesForHour[hour];
}

void populateColorCodes()
{
  // default night to red
  for (byte i = 0; i < HOURS_IN_DAY; i++)
  {
    colorCodesForHour[i] = CRGB::Red;
  }

  // daylight
  for (byte i = 8; i <= 20; i++)
  {
    colorCodesForHour[i] = CRGB::Blue;
  }
  // morning
  colorCodesForHour[6] = CRGB::Orange;
  colorCodesForHour[7] = CRGB::Green;
}