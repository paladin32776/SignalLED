#include "SignalLED.h"

SignalLED::SignalLED(unsigned char _pin)
{
  SignalLED(_pin, SLED_OFF, true);
}

SignalLED::SignalLED(unsigned char _pin, unsigned char _state)
{
  SignalLED(_pin, state, true);
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
  set_state(state);
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

void SignalLED::set_state(unsigned int _state)
{
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
  }
}
