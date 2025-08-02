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

#pragma endregion Functions

void BlinkOneLED(uint8_t ledPin) {
  uint8_t last_state = digitalRead(ledPin);
  digitalWrite(ledPin, !last_state);
  delay(LED_DELAY);
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
		delay(LED_DELAY);
	}
}

void StartAnimation(){
	LightLEDSOneByOne();
	delay(LED_DELAY);
	AllLEDS(LED_OFF);
	delay(LED_DELAY);
	AllLEDS(LED_ON);
	delay(LED_DELAY);
	AllLEDS(LED_OFF);
}

#endif // !_FUNCTIONS_H_
