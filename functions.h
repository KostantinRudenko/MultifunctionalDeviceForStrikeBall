#include "Arduino.h"
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

#pragma region ______________________________ FunctionsDefining

bool IsPirSensorActive();
bool IsChooseButtonPressed();
bool IsConfirmButtonPressed();
bool IsAnyButtonPressed();

bool BasicMode();
void OnlySirenMode();
bool OnlyIgniterMode();
bool TimerMode(const unsigned int& timer, bool& isTimerRunning);

#pragma endregion FunctionsDefining

#pragma region ______________________________ CommonFunctions

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
			bool sirenStoped = Siren.activateForSeconds(SIREN_TIME);
			bool igniterStoped = Igniter.acitvateForSeconds(IGNITER_TIME);
			if (sirenStoped && igniterStoped) {
				st = 0
				return true;
			}
		}
	return false;
}

void OnlySirenMode() {
  if (IsPirSensorActive()) {
    digitalWrite(SIREN_PIN, ON);
    delay(SIREN_WORK_TIME);
    digitalWrite(SIREN_PIN, OFF);
  }
  delay(BOUNCE_DELAY);
}

bool OnlyIgniterMode() {
  if (IsPirSensorActive()) {
    digitalWrite(IGNITER_PIN, ON);
    delay(IGNITER_DELAY);
    digitalWrite(IGNITER_PIN, OFF);
    return true;
  }
  delay(BOUNCE_DELAY);
  return false;
}

bool TimerMode(const unsigned int& timer, bool& isTimerRunning) {
  if (millis() > timer){
    digitalWrite(IGNITER_PIN, ON);
    digitalWrite(SIREN_PIN, ON);
    delay(SIREN_WORK_TIME);
    digitalWrite(SIREN_PIN, OFF);
    digitalWrite(IGNITER_PIN, OFF);
    isTimerRunning = false;
    return true;
  }
  return false;
}

#pragma endregion ModeFunctions

/*========================================================================
  ========================================================================*/

#endif // !_FUNCTIONS_H_
