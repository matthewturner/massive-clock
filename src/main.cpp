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
  show();
  delay(200);
  display.clear();
  display.setSeparator(true);
  show();
  delay(200);
  display.clear();
  display.setPart(1, 88, false);
  show();
  delay(200);
  display.clear();

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

  display.setPart(1, now.hour(), false);
  display.setPart(0, now.minute(), true);
  display.setSeparator(true);
  show();

  return false;
}

void show()
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