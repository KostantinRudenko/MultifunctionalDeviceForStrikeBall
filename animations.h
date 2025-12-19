#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_

#include <cstdint>
void setLedState(uint8_t& ledNum, const uint8_t& state) {
	digitalWrite(ledNum, state);
}

void setLedsState(uint8_t& ledsAmount, const uint8_t& state) {
	for (uint8_t i = 0; i < ledsAmount; i++) {
		digitalWrite(i, state);
	}
}

void stepLedProgressBar() {
	static uint8_t ledPosition = 0;
	ledPosition++ > LEDS_AMOUNT ? ledPosition = LEDS_AMOUNT : ledPosition++;
	digitalWrite(ledPosition, ON);
}


#endif _ANIMATIONS_H_
