#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma region ______________________________ Constants

#define ON  1
#define OFF 0

#define BTN_PRESSED  0
#define BTN_RELEASED 1

#define ACTIVE    1
#define NOTACTIVE 0

// Константы времени
const uint16_t WAITING_ANIMATION_INTERVAL_MS   = 50;
const uint16_t BUTTON_MONITORING_INTERVAL_MS   = 50;
const uint16_t AUTOSTART_TIME                  = 10 * 1000;
const uint16_t SIREN_TIME                      = 10 * 1000;
const uint16_t IGNITER_TIME                    = 3  * 1000;
const uint16_t TIMER_PERIOD					   = 5 * 60 * 1000;
// ==============================================

// Amount constants
const uint8_t GAMEMODES_AMOUNT    = 4;
const uint8_t LEDS_AMOUNT      	  = 6;
const uint8_t TIMER_SELECT_AMOUNT = 4;
// ==============================================

// Structures
enum DeviceStates {
	WAIT_INPUT,
	MODE_SELECT,
	MODE_CONFIRM,
	TIMER_SELECTION,
	TIMER_CONFIRM,
	AUTOSTART,
	RUNNING
};
enum GameModes {
	BASE_MODE,
	SIREN_ONLY_MODE,
	IGNITER_ONLY_MODE,
	TIMER_MODE
};
// ==============================================

// Pins
const uint8_t LED_PIN_1 = 0;
const uint8_t LED_PIN_2 = 1;
const uint8_t LED_PIN_3 = 2;
const uint8_t LED_PIN_4 = 3;
const uint8_t LED_PIN_5 = 4;
const uint8_t LED_PIN_6 = 5;
const uint8_t LEDS_ARRAY[] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_5, LED_PIN_6, LED_PIN_4};

const uint8_t PIR_SENSOR_PIN = 8;

const uint8_t SIREN_PIN = 7;
const uint8_t IGNITER_PIN = 6;

const uint8_t CHOOSE_BTN = 9;
const uint8_t CONFIRM_BTN = 10;
// ==============================================

#pragma endregion Constants

#endif // !_GLOBAL_H_
