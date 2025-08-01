
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ ConstantsAndVariables

bool isTimerRunning = false;

unsigned long time = 0;
uint8_t deviceState = 0;
GameMode gameMode = NONE;

#pragma endregion ConstantsAndVariables

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

  pinMode(MODE_BTN, INPUT);
  pinMode(TIMER_BTN, INPUT);

  StartAnimation();
}

void loop() {
  switch (deviceState) {
    case 0:
      if (digitalRead(MODE_BTN)) {
        deviceState++;
        break;
      }
    case 1:
      /* if (isTimerRunning && (milis() >= time)) {
        isTimerRunning = false;
        gameMode++;
        break;
      }
      else if (!isTimerRunning) {
        isTimerRunning = true;
        time = milis() + CONFIRM_TIME;
        break;
      } */
      WaitForConfirmingGameMode(isTimerRunning, gameMode, time);
      if (digitalRead(MODE_BTN)) {
        isTimerRunning = false;
        gameMode = static_cast<GameMode>((gameMode + 1) % 5);
      }
  }
}
