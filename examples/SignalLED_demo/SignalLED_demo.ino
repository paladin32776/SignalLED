#include "SignalLED.h"

SignalLED x(5, SLED_BLINK_FAST_3, false);
SignalLED y(4, SLED_BLINK_SLOW, false);

void setup()
{
}

void loop()
{
 x.check();
 y.check();
}
