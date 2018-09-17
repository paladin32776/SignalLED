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

	void set(unsigned int _state);

_state ... Desired initial LED state (SLED_OFF, SLED_ON, SLED_BLINK_SLOW, SLED_BLINK_FAST, SLED_BLINK_FAST_1, SLED_BLINK_FAST_3)<br>

Method to get LED state:

	unsigned int get();

Returns state of LED object.

Method to invert LED state:

	void invert();

Inverts state if SLED_ON or SLED_OFF. In all other cases sets state to SLED_OFF.<br>

Method containing logic:

	void check();

Call in main program loop().
