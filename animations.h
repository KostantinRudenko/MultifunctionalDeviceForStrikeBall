#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_

void setLedState(uint8_t ledNum, uint8_t state) {
	digitalWrite(ledNum, state);
}

void setLedsState(uint8_t ledsAmount, uint8_t state) {
	for (uint8_t i = 0; i < ledsAmount; i++) {
		digitalWrite(LEDS_ARRAY[i], state);
	}
}

bool stepLedProgressBar(bool reset = false, bool isForward = true) {
	static uint8_t ledPosition = 0;
	if (reset && isForward) {
		for (uint8_t i = 0; i < LEDS_AMOUNT; i++) digitalWrite(LEDS_ARRAY[i], OFF);
		ledPosition = 0;
		return false;
	}
	else if (reset && !isForward) {
		for (uint8_t i = 0; i < LEDS_AMOUNT; i++) digitalWrite(LEDS_ARRAY[i], ON);
		ledPosition = LEDS_AMOUNT-1;
		return false;
	}
	if (isForward) {
		if (ledPosition < LEDS_AMOUNT) {
			ledPosition++;
			digitalWrite(ledPosition, ON);
		}
		else return true;
	} else {
		if (ledPosition > 0) {
			ledPosition--;
			digitalWrite(ledPosition, OFF);
		}
		else return true;
	}
	return false;
}


#endif _ANIMATIONS_H_
