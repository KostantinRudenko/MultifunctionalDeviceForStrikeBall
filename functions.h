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
void RunningLEDLightUp();
void RunningLEDLightDown();

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

void RunningLEDLightUp() {
  for (uint8_t analog=0; analog<256; analog++) {
    analogWrite(LED_PIN_1, analog);
  }

  for (uint8_t ledNum=1; ledNum<LED_AMOUNT; ledNum++) {
    for (uint8_t analog=0; analog<256; analog++) {
      analogWrite(ledNum-1, 255-analog);
      analogWrite(ledNum, analog);
      //delay(LED_DELAY);
    }
	}
}

void RunningLEDLightDown() {
  for (uint8_t analog=0; analog<256; analog++) {
    analogWrite(LED_PIN_7, analog);
  }

  for (uint8_t ledNum=6; ledNum>-1; ledNum--) {
    for (uint8_t analog=0; analog<256; analog++) {
      analogWrite(ledNum+1, 255-analog);
      analogWrite(ledNum, analog);
      //delay(LED_DELAY);
    }
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
  AllLEDS(OFF);
  for (uint8_t ledNum=0; ledNum<LED_AMOUNT; ledNum++){
		digitalWrite(ledNum, ON);
		delay(delay_time);
	}
  AllLEDS(OFF);
}

bool IsPirSensorActive() {
  return digitalRead(PIR_SENSOR_PIN) == 1;
}

bool IsModeButtonClicked() {
  return digitalRead(MODE_BTN) == 1;
}

bool BasicMode() {
  if (IsPirSensorActive()) {
    digitalWrite(SIREN_PIN, ON);
    digitalWrite(IGNITER_PIN, ON);
    delay(IGNITER_DELAY);
    return true;
  }
  else {
    digitalWrite(SIREN_PIN, OFF);
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
