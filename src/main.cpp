#include "main.h"

void setup()
{
  Serial.begin(115200);

  pinMode(RECEIVE_PIN, INPUT);
  pinMode(TRANSMIT_PIN, OUTPUT);
  bluetoothSerial.begin(9600);

  pinMode(SHOW_PIN, INPUT_PULLUP);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);

  while (!Serial)
    ;

  setupRealtimeClock();
  setupColorSchedule();
  setupDisplaySchedule();
  setupTimezones();
  setupTest();

  commandListener.when("set", (EvtCommandAction)set);
  commandListener.when("set-schedule", (EvtCommandAction)setSchedule);
  commandListener.when("show", (EvtCommandAction)show);
  commandListener.when("status", (EvtCommandAction)status);
  commandListener.when("set-opt", (EvtCommandAction)setOptions);
  mgr.addListener(&commandListener);

  stateMachine.when(IDLE, (EvtAction)idle, UPDATING);
  stateMachine.when(SHOWING, (EvtAction)showing, UPDATING, STATE_FAILED, SHOW_TEMPORARILY_DURATION);
  stateMachine.when(UPDATING, (EvtAction)updating, IDLE);
  stateMachine.whenInterrupted(IDLE, SHOWING);
  stateMachine.transition(UPDATING);

  mgr.addListener(&stateMachine);
  attachInterrupt(digitalPinToInterrupt(SHOW_PIN), onInterrupt, FALLING);

  Serial.println(F("Setup complete. Continuing..."));
}

bool idle()
{
  Serial.println(F("Sleeping..."));
  Serial.flush();
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
  return true;
}

bool show()
{
  Serial.println(F("Command: SHOW"));
  stateMachine.transition(SHOWING);
  return true;
}

bool set(EvtListener *, EvtContext *, long data)
{
  Serial.print(F("Command: SET "));
  Serial.println(data);
  clock.adjust(DateTime(data));
  if (showAfterSet)
  {
    stateMachine.transition(SHOWING);
  }
  return true;
}

bool setSchedule(EvtListener *, EvtContext *, long data)
{
  Serial.print(F("Command: SET SCHEDULE "));
  Serial.println(data);
  displaySchedule.update(data);
  colorSchedule.update(data);
  if (showAfterSet)
  {
    stateMachine.transition(SHOWING);
  }
  return true;
}

bool status()
{
  Serial.println(F("Command: STATUS"));
  reportStatus();
  return true;
}

bool setOptions(EvtListener *, EvtContext *, long data)
{
  Serial.print(F("Command: SET-OPT "));
  Serial.println(data);
  showAfterSet = data % 10;
  return true;
}

bool updating()
{
  Serial.println(F("Updating..."));

  DateTime now = DateTime();
  if (CLOCK_IS_ENABLED)
  {
    now = toLocal(clock.now());
  }

  Flags mode = displaySchedule.valueFor(now.hour(), now.minute());
  if ((mode & Flags::STANDARD) == Flags::STANDARD || (mode & Flags::MINIMAL) == Flags::MINIMAL)
  {
    pendingDisplay.setPart(1, now.hour(), mode);
    pendingDisplay.setPart(0, now.minute(), (Flags)(mode | Flags::LEADING_ZERO));
    pendingDisplay.setSeparator((mode & Flags::SEPARATOR) == Flags::SEPARATOR);
  }
  else
  {
    pendingDisplay.clear();
  }

  CRGB::HTMLColorCode colorCode = colorFor(now.hour());
  pendingDisplay.setColor(colorCode);

  pendingDisplay.setBrightness(brightnessFrom(mode));

  if (display.updateFrom(&pendingDisplay))
  {
    render();
  }

  return true;
}

CRGB::HTMLColorCode colorFor(byte hour)
{
  byte colorIndex = colorSchedule.valueFor(hour);
  CRGB::HTMLColorCode colorCode = knownColors[colorIndex];
  return colorCode;
}

byte brightnessFrom(Flags mode)
{
  if ((mode & Flags::BRIGHT) == Flags::BRIGHT)
  {
    return BRIGHTNESS_BRIGHT;
  }
  return BRIGHTNESS_DIM;
}

bool showing()
{
  Serial.println(F("Showing temporarily..."));

  DateTime now = DateTime();
  if (CLOCK_IS_ENABLED)
  {
    now = toLocal(clock.now());
  }

  display.setPart(1, now.hour(), Flags::STANDARD);
  display.setPart(0, now.minute(), Flags::LEADING_ZERO);
  display.setSeparator(true);

  CRGB::HTMLColorCode colorCode = colorFor(now.hour());
  display.setColor(colorCode);

  Flags mode = displaySchedule.valueFor(now.hour(), now.minute());
  display.setBrightness(brightnessFrom(mode));

  render();

  return true;
}

void render()
{
  FastLED.setBrightness(display.getBrightness());
  CRGB::HTMLColorCode colorCode = (CRGB::HTMLColorCode)display.getColor();

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

DateTime toLocal(DateTime utc)
{
  time_t local = timezone->toLocal(utc.unixtime());
  return DateTime(local);
}

void reportStatus()
{
  bluetoothSerial.println(F("{"));
  bluetoothSerial.print(F("  \"time\": "));
  if (CLOCK_IS_ENABLED)
  {
    bluetoothSerial.print(clock.now().unixtime());
  }
  else
  {
    bluetoothSerial.print(0);
  }
  bluetoothSerial.println(F(","));
  bluetoothSerial.print(F("  \"schedules\": {"));
  bluetoothSerial.print(F("    \"display\": ["));
  for (byte i = 0; i < HOURS_IN_DAY; i++)
  {
    bluetoothSerial.print(displaySchedule.valueFor(i));
    if (i < HOURS_IN_DAY - 1)
    {
      bluetoothSerial.print(F(", "));
    }
  }
  bluetoothSerial.println(F("]"));
  bluetoothSerial.println(F("  }\n}"));
}

void setupColorSchedule()
{
  Serial.println(F("Setup color schedule..."));

  knownColors[0] = CRGB::Red;

  // daylight
  knownColors[1] = CRGB::Blue;
  colorSchedule.setup(8, 20, 1);
  // morning
  knownColors[2] = CRGB::Orange;
  colorSchedule.setup(6, 7, 2);
  // evening
  knownColors[3] = CRGB::Purple;
  colorSchedule.setup(21, 21, 3);
}

void setupDisplaySchedule()
{
  Serial.println(F("Setting up display schedule..."));

  // displaySchedule.setup(6, 6, Flags::MINIMAL);
  // displaySchedule.setup(7, 7, Flags::STANDARD);
  // displaySchedule.setup(10, 18, (Flags)(Flags::STANDARD | Flags::BRIGHT));
  // displaySchedule.setValueFor(20, BlockFlags::SECOND_HALF, Flags::STANDARD);
}

void setupRealtimeClock()
{
  if (!CLOCK_IS_ENABLED)
  {
    Serial.println(F("Clock is disabled"));
    return;
  }

  display.setBrightness(20);
  display.setColor(CRGB::Red);

  if (!clock.begin())
  {
    Serial.println(F("Couldn't find Realtime Clock"));
    Serial.flush();
    display.setText("cloc");
    render();
    delay(1000);
    abort();
  }

  if (clock.lostPower())
  {
    Serial.println(F("RTC lost power..."));
    display.setText("lost");
    render();
    delay(1000);
  }
}

void setupTest()
{
  Serial.println(F("Testing display 88..."));
  display.setPart(0, 88, Flags::NONE);
  display.setBrightness(20);
  display.setColor(CRGB::Blue);
  render();
  delay(200);
  display.clear();
  display.setSeparator(true);
  render();
  delay(200);
  display.clear();
  display.setPart(1, 88, Flags::NONE);
  render();
  delay(200);
  display.clear();
  display.setText("ello");
  display.setColor(CRGB::Green);
  render();
  delay(500);
  display.clear();
}

void setupTimezones()
{
  Serial.println(F("Setup timezones..."));

  timezone = new Timezone(
      TimeChangeRule("BST", Last, Sun, Mar, 1, 60),
      TimeChangeRule("GMT", Last, Sun, Oct, 2, 0));
}

void loop()
{
  mgr.loopIteration();
}

void onInterrupt()
{
  stateMachine.onInterrupt();
}