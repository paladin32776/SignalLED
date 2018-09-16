# Signalling with one LED. 

Signal different states with one LED. Possible LED states are: 
SLED_OFF, SLED_ON, SLED_BLINK_SLOW, SLED_BLINK_FAST, SLED_BLINK_FAST_1, SLED_BLINK_FAST_3

# Methods:

Constructors:

	SignalLED(unsigned char _pin);
	SignalLED(unsigned char _pin, unsigned char _state);
	SignalLED(unsigned char _pin, unsigned char _state, bool _active_low);

_pin ... LED pin<br>
_state ... Optional, default is SLED_OFF. Desired initial LED state (SLED_OFF, SLED_ON, SLED_BLINK_SLOW, SLED_BLINK_FAST, SLED_BLINK_FAST_1, SLED_BLINK_FAST_3)<br>
_active_low ... Optional, default is true. Set to true if LED is on when pin is LOW.<br>

Method to change LED state:

	void set_state(unsigned int _state);

_state ... Desired initial LED state (SLED_OFF, SLED_ON, SLED_BLINK_SLOW, SLED_BLINK_FAST, SLED_BLINK_FAST_1, SLED_BLINK_FAST_3)<br>

Method containing logic:

	void check();

Call in main program loop().

