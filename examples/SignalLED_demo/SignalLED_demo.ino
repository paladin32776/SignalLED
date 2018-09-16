#include "SignalLED.h"

SignalLED x(5, SLED_BLINK_FAST_3, true);

void setup()
{
}

void loop()
{
 x.check();
}
