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
  setupBrightnessSchedule();
  setupMinimalModeSchedule();
  setupTimezones();
  setupTest();

  stateMachine.when(IDLE, (EvtAction)idle, UPDATING);
  stateMachine.when(SHOWING, (EvtAction)showing, UPDATING, STATE_FAILED, SHOW_TEMPORARILY_DURATION);
  stateMachine.when(UPDATING, (EvtAction)updating, PROCESSING);
  stateMachine.when(PROCESSING, (EvtAction)processingCommands, IDLE);

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

bool processingCommands()
{
  commandReader.tryReadCommand(&command);
  switch (command.Value)
  {
  case Commands::CNONE:
    // nothing
    // Serial.println("Command: NONE");
    break;
  case Commands::SHOW:
    Serial.println(F("Command: SHOW"));
    stateMachine.transition(SHOWING);
    break;
  case Commands::SET:
    Serial.print(F("Command: SET "));
    Serial.println(command.Data);
    clock.adjust(DateTime(command.Data));
    stateMachine.transition(SHOWING);
    break;
  case Commands::STATUS:
    Serial.println(F("Command: STATUS"));
    reportStatus();
    break;
  default:
    Serial.print(F("Unknown command: "));
    Serial.println(command.Value);
    break;
  }
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

  if (displaySchedule.valueFor(now.hour()))
  {
    Flags mode = minimalSchedule.valueFor(now.hour());
    pendingDisplay.setPart(1, now.hour(), mode);
    pendingDisplay.setPart(0, now.minute(), (Flags)(mode | Flags::LEADING_ZERO));
    pendingDisplay.setSeparator(mode == Flags::NONE);
  }
  else
  {
    pendingDisplay.clear();
  }

  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());
  pendingDisplay.setColor(colorCode);
  byte brightness = brightnessSchedule.valueFor(now.hour());
  pendingDisplay.setBrightness(brightness);

  if (display.updateFrom(&pendingDisplay))
  {
    render();
  }

  return true;
}

bool showing()
{
  Serial.println(F("Showing temporarily..."));

  DateTime now = DateTime();
  if (CLOCK_IS_ENABLED)
  {
    now = toLocal(clock.now());
  }

  display.setPart(1, now.hour(), Flags::NONE);
  display.setPart(0, now.minute(), Flags::LEADING_ZERO);
  display.setSeparator(true);

  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());
  display.setColor(colorCode);
  byte brightness = brightnessSchedule.valueFor(now.hour());
  display.setBrightness(brightness);

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

byte minutesSinceMidnight(DateTime local)
{
  byte minutes = local.hour() * 60 + local.minute();
}

void reportStatus()
{
  bluetoothSerial.println(F("{"));
  bluetoothSerial.print(F("  \"time\": "));
  if (CLOCK_IS_ENABLED)
  {
    bluetoothSerial.println(clock.now().unixtime());
  }
  else
  {
    bluetoothSerial.println(0);
  }
  bluetoothSerial.println(F("}"));
}

void setupColorSchedule()
{
  Serial.println(F("Setup color schedule..."));
  // daylight
  colorSchedule.setup(8, 20, CRGB::Blue);
  // morning
  colorSchedule.setup(6, 7, CRGB::Orange);
  // evening
  colorSchedule.setup(21, 21, CRGB::Purple);
}

void setupDisplaySchedule()
{
  Serial.println(F("Setting up display schedule..."));

  separatorSchedule.setup(6, 10, true);
  separatorSchedule.setup(19, 21, true);
  displaySchedule.setup(19, 21, true);

  if (CURRENT_SCHEDULE == SUMMER_SCHEDULE)
  {
    displaySchedule.setup(6, 9, true);
  }
  else
  {
    displaySchedule.setup(7, 9, true);
  }
}

void setupBrightnessSchedule()
{
  Serial.println(F("Setting up brightness schedule..."));
  brightnessSchedule.setup(10, 18, 40);
}

void setupMinimalModeSchedule()
{
  Serial.println(F("Setting up minimal mode schedule..."));
  minimalSchedule.setup(6, 6, Flags::SUPER_MINIMAL);
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
    Serial.println(F("Realtime Clock lost power, setting the time..."));
    display.setText("lost");
    render();
    delay(1000);
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  if (digitalRead(SHOW_PIN) == LOW)
  {
    Serial.println(F("Manual override: setting the time..."));
    display.setText("rset");
    render();
    delay(1000);
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
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