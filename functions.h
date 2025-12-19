#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

/*========================================================================
  ========================================================================*/

#pragma region ______________________________ Functions

bool IsPirSensorActive();
bool IsChooseButtonClicked();

bool BasicMode();
void OnlySirenMode();
bool OnlyIgniterMode();
bool TimerMode(const unsigned int& timer, bool& isTimerRunning);

#pragma endregion Functions

#pragma region ______________________________ ExecutingFunctions


#pragma endregion ExecutingFunctions

#pragma region ______________________________ StateFunctions

bool IsPirSensorActive() {
  return digitalRead(PIR_SENSOR_PIN) == ACTIVE;
}

bool IsChooseButtonClicked() {
  return digitalRead(CHOOSE_BTN) == BTN_PRESSED;
}

#pragma endregion StateFunctions

#pragma region ______________________________ ModeFunctions

bool BasicMode() {
  if (IsPirSensorActive()) {
    digitalWrite(SIREN_PIN, ON);
    digitalWrite(IGNITER_PIN, ON);
    delay(IGNITER_DELAY);
    return true;
  }
  else {
    digitalWrite(IGNITER_PIN, OFF);
  }
  delay(BOUNCE_DELAY);
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
