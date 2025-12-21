#include "Arduino.h"
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

#pragma region ______________________________ CommonFunctions

void setLedsState(uint8_t ledsAmount, uint8_t state);

void setPinState(uint8_t pin, bool v) {
  digitalWrite(pin, v);
}

bool millisTimer(uint32_t time, bool reset = false) {
	static uint32_t startTime;
	static bool isRunning = false;

	if (reset) {
		isRunning = false;
		return false;
	}

	if (!isRunning) {
		isRunning = true;
		startTime = millis();
	}

	if (millis() - startTime > time) {
		isRunning = false;
		return true;
	}
	else return false;
}

#pragma endregion CommonFunctions

#pragma region ______________________________ StateFunctions

bool IsPirSensorActive() {
  return digitalRead(PIR_SENSOR_PIN) == ACTIVE;
}

#pragma endregion StateFunctions

#pragma region ______________________________ ModeFunctions

bool BasicMode(InputDevice& PIR, OutputDevice& Siren, OutputDevice& Igniter) {
	static uint8_t st = 0;
	switch (st) {
		case 0:
			if (PIR.isActive()) {
				st = 1;
			}
			break;
		case 1:
			bool sirenStoped = Siren.activateForMiliseconds(SIREN_TIME);
			bool igniterStoped = Igniter.activateForMiliseconds(IGNITER_TIME);
			if (sirenStoped && igniterStoped) {
				st = 0;
				return true;
			}
		}
	return false;
}

bool OnlySirenMode(InputDevice& PIR, OutputDevice& Siren) {
	static uint8_t st = 0;
	switch (st) {
		case 0:
		if (PIR.isActive()) {
			st = 1;
		}
		break;
		case 1:
		bool sirenStoped = Siren.activateForMiliseconds(SIREN_TIME);
		if (sirenStoped) {
			st = 0;
			return true;
		}
		break;
	}
	return false;
}

bool OnlyIgniterMode(InputDevice& PIR, OutputDevice& Igniter) {
	static uint8_t st = 0;
	switch (st) {
		case 0:
		if (PIR.isActive()) {
			st = 1;
		}
		break;
		case 1:
		bool igniterStoped = Igniter.activateForMiliseconds(IGNITER_TIME);
		if (igniterStoped) {
			st = 0;
			return true;
		}
		break;
	}
	return false;
}

bool TimerMode(uint32_t timerTimePeriod, OutputDevice& Igniter) {
	static uint32_t startTime = millis();
	static uint32_t ledStepForTimer = timerTimePeriod/LEDS_AMOUNT;
	static uint8_t barLedsAmount = LEDS_AMOUNT;
	static uint8_t st = 0;

	switch (st) {
		case 0:
			if (map(millis()-startTime,0,timerTimePeriod,0,LEDS_AMOUNT) < barLedsAmount && barLedsAmount > 0) {
				setLedsState(LEDS_AMOUNT, OFF);
				setLedsState(barLedsAmount, ON);
			}
			if (millis()-startTime > timerTimePeriod) {
				st = 1;
			}
			break;
		case 1:
			bool igniterStoped = Igniter.activateForMiliseconds(IGNITER_TIME);
			if (igniterStoped) {
				st = 0;
				return true;
			}
			break;
	}
	return false;
}

#pragma endregion ModeFunctions

/*========================================================================
  ========================================================================*/

#endif // !_FUNCTIONS_H_
