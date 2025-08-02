#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma region ______________________________ Constants

#define LED_ON  1
#define LED_OFF 0

const uint8_t BUTTON_DELAY = 250;
const uint8_t LED_DELAY = 250;


const uint8_t LED_AMOUNT = 7;

const uint8_t LED_1_RED_PIN = 0;
const uint8_t LED_2_RED_PIN = 1;
const uint8_t LED_3_RED_PIN = 2;
const uint8_t LED_4_RED_PIN = 3;
const uint8_t LED_5_RED_PIN = 4;
const uint8_t LED_6_GREEN_PIN = 5;
const uint8_t LED_7_GREEN_PIN = 6;

const uint8_t PIR_SENSOR_PIN = 9;

const uint8_t SIREN_PIN = 7;
const uint8_t IGNITER_PIN = 10;

const uint8_t MODE_BTN = 20;
const uint8_t TIMER_BTN = 21;

const unsigned int CONFIRM_TIME = 5000;
const unsigned int AUTOSTART_TIME = 5000;

#endif // !_GLOBAL_H_
