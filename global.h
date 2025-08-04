#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma region ______________________________ Constants

#define ON  1
#define OFF 0

// Константы времени
const uint8_t BUTTON_DELAY = 150;
const uint8_t LED_DELAY = 250;
const uint8_t RUNNING_LED_DELAY = 50;
const uint8_t BOUNCE_DELAY = 50;
const uint16_t IGNITER_DELAY = 500;
const uint16_t PAUSE_DELAY = 500;

const uint16_t SIREN_WORK_TIME = 10000;

const uint16_t ONE_SECOND_PERIOD = 1000;
const long TEN_MINUTE_PERIOD = 5000; //600000;

const unsigned int AUTOSTART_TIME = 5000;
// ==============================================

// Статус кнопки
const uint8_t BUTTON_CLICKED = 0;
// ==============================================

// Константы количества
const uint8_t LED_AMOUNT = 6;
const uint8_t MODES_AMOUNT = 4;
const uint8_t TIMER_PERIODS_AMOUNT = 5;
// ==============================================

// Константы пинов
const uint8_t LED_PIN_1 = 0;
const uint8_t LED_PIN_2 = 1;
const uint8_t LED_PIN_3 = 2;
const uint8_t LED_PIN_4 = 3;
const uint8_t LED_PIN_5 = 4;
const uint8_t LED_PIN_6 = 5;
//const uint8_t LED_PIN_7 = 6;

const uint8_t PIR_SENSOR_PIN = 6;

const uint8_t SIREN_PIN = 7;
const uint8_t IGNITER_PIN = 10;

const uint8_t CHOOSE_BTN = 20;
const uint8_t CONFIRM_BTN = 21;
// ==============================================

#pragma endregion Constants

#endif // !_GLOBAL_H_
