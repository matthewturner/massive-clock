#include "main.h"

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(5);

  while (!Serial)
    ;

  setupRealtimeClock();
  setupColorCodes();
  setupDisplayHours();
  setupTest();

  mgr.addListener(new EvtTimeListener(500, true, (EvtAction)update));

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  mgr.loopIteration();
}

bool update()
{
  now = clock.now();

  if (!displaySchedule.valueFor(now.hour()))
  {
    display.hide();
    render();
    return false;
  }

  display.setPart(1, now.hour(), false);
  display.setPart(0, now.minute(), true);
  display.setSeparator(true);
  render();

  return false;
}

void render()
{
  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());

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

void setupColorCodes()
{
  Serial.println("Populating colors...");
  // daylight
  colorSchedule.setup(8, 20, CRGB::Blue);
  // morning
  colorSchedule.setup(6, 7, CRGB::Orange);
  // evening
  colorSchedule.setup(21, 21, CRGB::Purple);
}

void setupDisplayHours()
{
  Serial.println("Setting up display hours...");
  displaySchedule.setup(6, 21, true);
}

void setupRealtimeClock()
{
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
}

void setupTest()
{
  Serial.println("Testing display 88...");
  display.setPart(0, 88, false);
  render();
  delay(200);
  display.clear();
  display.setSeparator(true);
  render();
  delay(200);
  display.clear();
  display.setPart(1, 88, false);
  render();
  delay(200);
  display.clear();
}