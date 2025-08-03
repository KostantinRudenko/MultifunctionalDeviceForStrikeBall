#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma region ______________________________ Constants

#define ON  1
#define OFF 0

const uint8_t BUTTON_DELAY = 250;
const uint8_t LED_DELAY = 250;
const uint8_t BOUNCE_DELAY = 50;
const uint16_t IGNITER_DELAY = 500;

const uint8_t BUTTON_CLICKED = 0;

const uint8_t LED_AMOUNT = 7;
const uint8_t MODES_AMOUNT = 4;

const uint8_t LED_PIN_1 = 0;
const uint8_t LED_PIN_2 = 1;
const uint8_t LED_PIN_3 = 2;
const uint8_t LED_PIN_4 = 3;
const uint8_t LED_PIN_5 = 4;
const uint8_t LED_PIN_6 = 5;
const uint8_t LED_PIN_7 = 6;

const uint8_t PIR_SENSOR_PIN = 9;

const uint8_t SIREN_PIN = 7;
const uint8_t IGNITER_PIN = 10;

const uint8_t MODE_BTN = 20;
const uint8_t TIMER_BTN = 21;

const unsigned int CONFIRM_TIME = 5000;
const unsigned int AUTOSTART_TIME = 5000;

#endif // !_GLOBAL_H_
