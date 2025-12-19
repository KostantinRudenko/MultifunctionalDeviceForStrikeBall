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

void stepLedProgressBar(bool reset = false) {
	static uint8_t ledPosition = 0;
	if (reset) {
		for (uint8_t i = 0; i < LEDS_AMOUNT; i++) digitalWrite(LEDS_ARRAY[i], OFF);
		ledPosition = 0;
		return;
	}
	if (ledPosition < LEDS_AMOUNT) {
		ledPosition++;
		digitalWrite(ledPosition, ON);
	}
}


#endif _ANIMATIONS_H_
