#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#pragma region ______________________________ Constants

const uint8_t LED_AMOUNT = 7;
const int LIGHT_DELAY = 250;

#pragma endregion Constants

#pragma region ______________________________ Variables

unsigned float time;

#pragma endregion Variables

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

#endif // !_FUNCTIONS_H_
