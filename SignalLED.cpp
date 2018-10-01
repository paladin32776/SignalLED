#include "SignalLED.h"

SignalLED::SignalLED(unsigned char _pin)
{
  SignalLED(_pin, SLED_OFF, true);
}

SignalLED::SignalLED(unsigned char _pin, unsigned char _state)
{
  SignalLED(_pin, _state, true);
}

SignalLED::SignalLED(unsigned char _pin, unsigned char _state, bool _active_low)
{
  pin = _pin;
  state = _state;
  active_low = _active_low;
  pinMode(pin, OUTPUT);
  set_led(false);
  etp_slow = new EnoughTimePassed(SLED_TIME_SLOW);
  etp_fast = new EnoughTimePassed(SLED_TIME_FAST);
  etp_pulse = new EnoughTimePassed(SLED_TIME_PULSE);
  set(state);
}

SignalLED::~SignalLED()
{
  delete etp_slow;
  delete etp_fast;
}

void SignalLED::set_led(bool _led)
{
  led = _led;
  digitalWrite(pin, active_low != led);
}

void SignalLED::invert_led()
{
  led = !led;
  set_led(led);
}

void SignalLED::set(unsigned int _state)
{
  if (state==_state)
    return;
  state = _state;
  switch (state)
  {
    case SLED_BLINK_FAST:
      etp_fast->prime();
      break;
    case SLED_BLINK_SLOW:
    case SLED_BLINK_FAST_1:
    case SLED_BLINK_FAST_3:
      etp_slow->prime();
      break;
    case SLED_PULSE:
      etp_pulse->event();
      break;
  }
}

unsigned int SignalLED::get()
{
  return state;
}

void SignalLED::invert()
{
  switch (state)
  {
    case SLED_OFF:
      state = SLED_ON;
      break;
    case SLED_ON:
      state = SLED_OFF;
      break;
  }
}

void SignalLED::check()
{
  switch (state)
  {
    case SLED_OFF:
      set_led(false);
      break;
    case SLED_ON:
      set_led(true);
      break;
    case SLED_BLINK_FAST:
      if (etp_fast->enough_time())
        invert_led();
      break;
    case SLED_BLINK_SLOW:
      if (etp_slow->enough_time())
        invert_led();
      break;
    case SLED_BLINK_FAST_1:
      if (etp_slow->enough_time())
      {
        etp_fast->event(); // Sync fast events
        set_led(true);
      }
      if (etp_fast->enough_time())
        set_led(false);
      break;
    case SLED_BLINK_FAST_3:
      if (etp_slow->enough_time())
      {
        etp_fast->event(); // Sync fast events
        blink_counter = 5;
        set_led(true);
      }
      if (etp_fast->enough_time() && blink_counter>0)
      {
        blink_counter--;
        invert_led();
      }
      break;
    case SLED_PULSE:
      set_led(true);
      if (etp_pulse->enough_time())
        set(SLED_OFF);
      break;
  }
}
