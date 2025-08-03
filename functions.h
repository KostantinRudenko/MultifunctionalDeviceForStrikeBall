#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

#pragma region ______________________________ Functions

void BlinkOneLED(uint8_t ledPin);
void AllLEDS(uint8_t state);
void LightLEDSOneByOne();
void StartAnimation();
void AutostartAnimation();
bool RunningLEDLightUpAndCheckingButton();

bool IsPirSensorActive();
bool IsModeButtonClicked();

bool BasicMode();
void OnlySirenMode();
bool OnlyIgniterMode();
void TimerMode(const unsigned int& timer, bool& isTimerRunning);

#pragma endregion Functions

void BlinkOneLED(uint8_t ledPin) {
  uint8_t last_state = digitalRead(ledPin);
  digitalWrite(ledPin, !last_state);
  delay(LED_DELAY);
  digitalWrite(ledPin, last_state);
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

bool RunningLEDLightUpAndCheckingButton() {
  digitalWrite(LED_PIN_1, ON);
  delay(RUNNING_LED_DELAY);

  for (uint8_t ledNum=1; ledNum<LED_AMOUNT; ledNum++) {
    digitalWrite(ledNum, ON);
    digitalWrite(ledNum-1, OFF);
    delay(RUNNING_LED_DELAY);
    if (IsModeButtonClicked()) {
      return true;
    }
  }

  digitalWrite(LED_PIN_7, ON);
  delay(RUNNING_LED_DELAY);

  for (short ledNum=6; ledNum>=0; ledNum--) {
    digitalWrite(ledNum, ON);
    digitalWrite(ledNum+1, OFF);
    delay(RUNNING_LED_DELAY);
    if (IsModeButtonClicked()) {
      return true;
    }
  }
  return false;
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

bool IsPirSensorActive() {
  return digitalRead(PIR_SENSOR_PIN) == 1;
}

bool IsModeButtonClicked() {
  return digitalRead(MODE_BTN) == BUTTON_CLICKED;
}

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
  }
  else {
    digitalWrite(SIREN_PIN, OFF);
  }
  delay(BOUNCE_DELAY);
}

bool OnlyIgniterMode() {
  if (IsPirSensorActive()) {
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

void TimerMode(const unsigned int& timer, bool& isTimerRunning) {
  if (millis() > timer){
    digitalWrite(IGNITER_PIN, ON);
    delay(IGNITER_DELAY);
    isTimerRunning = false;
  }
}

#endif // !_FUNCTIONS_H_
