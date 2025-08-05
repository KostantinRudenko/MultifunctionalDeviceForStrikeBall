#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

/*========================================================================
  ========================================================================*/

#pragma region ______________________________ Functions

void BlinkOneLED(uint8_t ledPin);
void BlinkOneLEDWithCustomMilisecondsDelay(uint8_t ledPin, const uint16_t& delayTime);
void AllLEDS(uint8_t state);
void LightLEDSOneByOne();
void LightLEDsFromFirstTo(uint8_t& lastLedPin);
void StartAnimation();
void AutostartAnimation();
bool RunningLEDLightAndCheckingButton();
bool SelectTimeForTimer(uint8_t& choosenTimer);
void UpdateLedsForTimerMode(const unsigned long& timer);

bool IsPirSensorActive();
bool IsChooseButtonClicked();

bool BasicMode();
void OnlySirenMode();
bool OnlyIgniterMode();
bool TimerMode(const unsigned int& timer, bool& isTimerRunning);

#pragma endregion Functions

/*========================================================================
  ========================================================================*/

#pragma region ______________________________ ExecutingFunctions

void BlinkOneLED(uint8_t ledPin) {
  uint8_t last_state = digitalRead(ledPin);
  digitalWrite(ledPin, !last_state);
  delay(LED_DELAY);
  digitalWrite(ledPin, last_state);
}

void BlinkOneLEDWithCustomMilisecondsDelay(uint8_t ledPin, const uint16_t& delayTime) {
  uint8_t last_state = digitalRead(ledPin);
  delay(delayTime);
  digitalWrite(ledPin, !last_state);
  delay(delayTime);
  digitalWrite(ledPin, last_state);
}

void BlinkSomeLEDs(uint8_t ledPinAmount) {
  for (uint8_t ledPin; ledPin<ledPinAmount; ledPin++) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(LED_DELAY);
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void AllLEDS(uint8_t state) {
	for (uint8_t ledNum=0; ledNum<LED_AMOUNT; ledNum++){
		digitalWrite(ledNum, state);
	}
}

void LightLEDSOneByOne() {
	for (uint8_t ledNum=0; ledNum<LED_AMOUNT; ledNum++){
		digitalWrite(ledNum, ON);
		delay(LED_DELAY);
	}
}

void LightLEDsFromFirstTo(uint8_t& lastLedPin) {
  for (uint8_t ledPin=0; ledPin<=lastLedPin; ledPin++) {
    digitalWrite(ledPin, ON);
  }
}

void StartAnimation() {
	LightLEDSOneByOne();
	delay(LED_DELAY);
	AllLEDS(OFF);
	delay(LED_DELAY);
	AllLEDS(ON);
	delay(LED_DELAY);
	AllLEDS(OFF);
}

void AutostartAnimation(){
  unsigned int delay_time = (LED_AMOUNT*LED_DELAY + AUTOSTART_TIME)/LED_AMOUNT;
  AllLEDS(ON);
  for (short ledNum=6; ledNum>=0; ledNum--){
		digitalWrite(ledNum, OFF);
		delay(delay_time);
	}
  AllLEDS(OFF);
}

bool RunningLEDLightAndCheckingButton() {
  digitalWrite(LED_PIN_1, ON);
  delay(RUNNING_LED_DELAY);

  for (uint8_t ledNum=1; ledNum<LED_AMOUNT; ledNum++) {
    digitalWrite(ledNum, ON);
    digitalWrite(ledNum-1, OFF);
    delay(RUNNING_LED_DELAY);
    if (IsChooseButtonClicked()) {
      return true;
    }
  }

  digitalWrite(LED_PIN_6, ON);
  delay(RUNNING_LED_DELAY);

  for (short ledNum=6; ledNum>=0; ledNum--) {
    digitalWrite(ledNum, ON);
    digitalWrite(ledNum+1, OFF);
    delay(RUNNING_LED_DELAY);
    if (IsChooseButtonClicked()) {
      return true;
    }
  }
  return false;
}

bool SelectTimeForTimer(uint8_t& timerSelectedPosition) {
  if (digitalRead(CHOOSE_BTN) == BUTTON_CLICKED) {
    timerSelectedPosition = (timerSelectedPosition+1) % TIMER_PERIODS_AMOUNT;
  }
  else if (digitalRead(CONFIRM_BTN) == BUTTON_CLICKED) {
    return true;
  }
  AllLEDS(OFF);
  LightLEDsFromFirstTo(timerSelectedPosition);
  delay(BUTTON_DELAY);
  return false;
}

void UpdateLedsForTimerMode(const unsigned long& timer, const uint8_t& choosenTimer) {
  AllLEDS(OFF);
  uint8_t timerLedPinsLeft = map(millis(), 0, timer, 0, choosenTimer);
  LightLEDsFromFirstTo(timerLedPinsLeft);
  BlinkOneLEDWithCustomMilisecondsDelay(LED_PIN_6, ONE_SECOND_PERIOD);
}

#pragma endregion ExecutingFunctions

/*========================================================================
  ========================================================================*/

#pragma region ______________________________ StateFunctions

bool IsPirSensorActive() {
  delay(1000);
  return digitalRead(PIR_SENSOR_PIN) == 1;
}

bool IsChooseButtonClicked() {
  return digitalRead(CHOOSE_BTN) == BUTTON_CLICKED;
}

#pragma endregion StateFunctions

/*========================================================================
  ========================================================================*/

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
