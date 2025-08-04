
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

/* ---------- Режими ----------
 * 0 - Базовый режим (сирена + зажигатель)
 * 1 - Режим только сирены
 * 2 - Режим только зажигателя
 * 3 - Таймер с зажигателем
 * Номер светодиода соответствует номеру режима
 * ---------------------------- */

uint8_t state = 0;
uint8_t gMode = 0;
uint8_t modeLedPin = 0;
uint8_t timerSelectedPosition = 0;

unsigned long timer = 0;

bool isTimerRunning = false;

#pragma endregion Variables

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(LED_PIN_6, OUTPUT);
  pinMode(LED_PIN_7, OUTPUT);

  pinMode(PIR_SENSOR_PIN, INPUT);

  pinMode(SIREN_PIN, OUTPUT);
  pinMode(IGNITER_PIN, OUTPUT);

  pinMode(CHOOSE_BTN, INPUT_PULLUP);
  pinMode(CONFIRM_BTN, INPUT_PULLUP);

  StartAnimation();
}

void loop() {
  switch (state) {
    case 0: // Ожидание нажатия кнопки
      if (RunningLEDLightAndCheckingButton()) {
        state = 1;
        AllLEDS(OFF);
        delay(PAUSE_DELAY);
        break;
      }
      state = 0;
      break;

    case 1: // Выбор режима
      if (digitalRead(CHOOSE_BTN) == BUTTON_CLICKED) {
        gMode = (gMode+1) % MODES_AMOUNT;
        modeLedPin = gMode;
      }
      AllLEDS(OFF);
      digitalWrite(modeLedPin, ON);
      delay(BUTTON_DELAY);
      state = 2;

    case 2: // Ожидание подтверждения режима
      if (digitalRead(CONFIRM_BTN) == BUTTON_CLICKED) {
        BlinkOneLED(modeLedPin);
        delay(LED_DELAY);
        digitalWrite(modeLedPin, OFF);
        
        state = 3;
        break;
      }

      state = 1;
      break;

    case 3: // запуск режима
      if (gMode == 3) {
        if (SelectTimeForTimer(timerSelectedPosition)) {
          state = 4;
        }
        break;
      }
      
      AutostartAnimation();
      state = 4;
      break;
  
    case 4: // Выбор и работа игрового режима
      switch (gMode) {
        case 0:
          if (BasicMode()) {
            delay(SIREN_WORK_TIME);
            digitalWrite(SIREN_PIN, OFF);
            digitalWrite(IGNITER_PIN, OFF);
            state = 0;
          }
          break;
        
        case 1:
          OnlySirenMode();
          break;
        
        case 2:
          if (OnlyIgniterMode()) {
            state = 0;
          }
          break;

        case 3:
          if (!isTimerRunning) {
            timer = millis() + timerSelectedPosition * TEN_MINUTE_PERIOD;
            isTimerRunning = true;
          }
          if (TimerMode(timer, isTimerRunning)) {
            state = 0;
            break;
          }
          AllLEDS(OFF);
          LightLEDsFromFirstTo(timerSelectedPosition);
          BlinkOneLEDWithCustomMilisecondsDelay(timerSelectedPosition, ONE_SECOND_PERIOD);
          break;
    }
  }
}
