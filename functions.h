#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Includes

#include "global.h"

#pragma endregion Includes

#pragma region ______________________________ Constants

const uint8_t LED_AMOUNT = 7;
const int LIGHT_DELAY = 250;

#pragma endregion Constants

#pragma region ______________________________ Functions

void BlinkOneLED(uint8_t ledPin);
void AllLEDS(uint8_t state);
void LightLEDSOneByOne();
void StartAnimation();
void WaitForConfirmingGameMode(bool& isTimerRunning, GameMode& gameMode, unsigned long& time);
void CheckGameMode(GameMode& gameMode);

#pragma endregion Functions

void BlinkOneLED(uint8_t ledPin) {
  uint8_t last_state = digitalRead(ledPin);
  digitalWrite(ledPin, !last_state);
  delay(250);
  digitalWrite(ledPin, last_state);
}

void AllLEDS(uint8_t state){
	for (uint8_t ledNum=0; ledNum<LED_AMOUNT; ledNum++){
		digitalWrite(ledNum, state);
	}
}

void LightLEDSOneByOne(){
	for (uint8_t ledNum=0; ledNum<LED_AMOUNT; ledNum++){
		digitalWrite(ledNum, LED_ON);
		delay(LIGHT_DELAY);
	}
}

void StartAnimation(){
	LightLEDSOneByOne();
	delay(LIGHT_DELAY);
	AllLEDS(LED_OFF);
	delay(LIGHT_DELAY);
	AllLEDS(LED_ON);
	delay(LIGHT_DELAY);
	AllLEDS(LED_OFF);
}

void WaitForConfirmingGameMode(bool& isTimerRunning, GameMode& gameMode, unsigned long& time) {
	if (isTimerRunning && (millis() >= time)) {
        isTimerRunning = false;
		CheckGameMode(gameMode);
    }
    else if (!isTimerRunning) {
    	isTimerRunning = true;
        time = millis() + CONFIRM_TIME;
    }
}

void CheckGameMode(GameMode& gameMode) {
	switch (gameMode) {
		case NONE:
			break;
		case BASE:
			AllLEDS(LED_OFF);
			digitalWrite(LED_1_RED_PIN, LED_ON);
			break;
		case SIREN_ONLY:
			AllLEDS(LED_OFF);
			digitalWrite(LED_2_RED_PIN, LED_ON);
			break;
		case IGNITER_ONLY:
			AllLEDS(LED_OFF);
			digitalWrite(LED_3_RED_PIN, LED_ON);
			break;
		case TIMER:
			AllLEDS(LED_OFF);
			digitalWrite(LED_4_RED_PIN, LED_ON);
			break;
	}
}

#endif // !_FUNCTIONS_H_
