
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

/* ---------- Game Modes ----------
 * 0 - None
 * 1 - Basic mode
 * 2 - Siren only mode
 * 3 - Igniter only mode
 * 4 - Timer mode with igniter
 * Led number is same to the game mode number so modeLedPin=gMode
 * -------------------------------- */


uint8_t gMode = 0;
uint8_t modeLedPin = gMode;
unsigned long timer = 0;
bool isTimerRunning = false;
bool isModeChoosen = false;

#pragma endregion Variables

void setup() {
  pinMode(LED_1_RED_PIN, OUTPUT);
  pinMode(LED_2_RED_PIN, OUTPUT);
  pinMode(LED_3_RED_PIN, OUTPUT);
  pinMode(LED_4_RED_PIN, OUTPUT);
  pinMode(LED_5_RED_PIN, OUTPUT);
  pinMode(LED_6_GREEN_PIN, OUTPUT);
  pinMode(LED_7_GREEN_PIN, OUTPUT);

  pinMode(PIR_SENSOR_PIN, INPUT);

  pinMode(SIREN_PIN, OUTPUT);
  pinMode(IGNITER_PIN, OUTPUT);

  pinMode(MODE_BTN, INPUT_PULLUP);
  pinMode(TIMER_BTN, INPUT_PULLUP);

  StartAnimation();
}

void loop() {
  if (digitalRead(MODE_BTN) == 0 && !isModeChoosen) {
        gMode = (gMode+1) % 5;
        modeLedPin = gMode;
        timer = millis() + CONFIRM_TIME;
        isTimerRunning = true;
        isModeChoosen = false;
  }
  if (isTimerRunning && (millis() > timer) && (!gMode == 0)) {
    isTimerRunning = false;
    isModeChoosen = true;
    digitalWrite(modeLedPin, LED_OFF);
    delay(LED_DELAY);
    digitalWrite(modeLedPin, LED_ON);
    delay(LED_DELAY);
    digitalWrite(modeLedPin, LED_OFF);
  }
  /* switch (gMode) {
    case 0: // None
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
    case 1: // Basic
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
    case 2: // Siren only
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
    case 3: // Igniter only
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
    case 4: // Timer
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
  } */
  if (!modeLedPin) {
    AllLEDS(LED_OFF);
    digitalWrite(modeLedPin, LED_ON);
    delay(BUTTON_DELAY);
  }
}
