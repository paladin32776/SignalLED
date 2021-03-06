#include "Arduino.h"
#include "EnoughTimePassed.h"

#define SLED_OFF 0
#define SLED_ON 1
#define SLED_BLINK_SLOW 2
#define SLED_BLINK_FAST 3
#define SLED_BLINK_FAST_1 4
#define SLED_BLINK_FAST_3 5
#define SLED_PULSE 6

#define SLED_TIME_SLOW 1000
#define SLED_TIME_FAST 100
#define SLED_TIME_PULSE 500

#ifndef SIGNALLED_H
#define SIGNALLED_H

class SignalLED
{
  private:
    unsigned char pin;
    bool led;
    unsigned char state;
    bool active_low;
    unsigned char blink_counter;
    EnoughTimePassed* etp_slow;
    EnoughTimePassed* etp_fast;
    EnoughTimePassed* etp_pulse;
    bool pulse;
    void set_led(bool _led);
    void invert_led();
  public:
    SignalLED(unsigned char _pin);
    SignalLED(unsigned char _pin, unsigned char _state);
    SignalLED(unsigned char _pin, unsigned char _state, bool _active_low);
    ~SignalLED();
    unsigned int set(unsigned int _state);
    unsigned int get();
    unsigned int invert();
    void check();
};

#endif // SIGNALLED_H
