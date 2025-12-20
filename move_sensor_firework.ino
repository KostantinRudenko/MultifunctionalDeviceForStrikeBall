
#pragma region ______________________________ Includes

#include "global.h"
#include "animations.h"
#include "functions.h"
#include "button.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

/* ---------- Режими ----------
 * 0 - Базовый режим (сирена + зажигатель)
 * 1 - Режим только сирены
 * 2 - Режим только зажигателя
 * 3 - Таймер с зажигателем
 * Номер светодиода соответствует номеру режима
 * ---------------------------- */

uint8_t state = WAIT_INPUT;
uint8_t gMode = BASE_MODE;
uint8_t timerSelectedPosition = 0;
uint8_t choosenTimer = 0;

unsigned long timer = 0;

bool isTimerSelectionActivated = false;
bool isTimerRunning = false;

#pragma endregion Variables

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(LED_PIN_6, OUTPUT);

  pinMode(PIR_SENSOR_PIN, INPUT);

  pinMode(SIREN_PIN, OUTPUT);
  pinMode(IGNITER_PIN, OUTPUT);

  pinMode(CHOOSE_BTN, INPUT_PULLUP);
  pinMode(CONFIRM_BTN, INPUT_PULLUP);

  Button chooseButton(CHOOSE_BTN);
  Button confirmButton(CONFIRM_BTN);
}

void loop() {
  switch (state) {
    case WAIT_INPUT: // Ожидание нажатия кнопки
      static bool isForward = true;

      if (millisTimer(WAITING_ANIMATION_INTERVAL_MS)) {
        if ( && stepLedProgressBar(false,isForward) {
            isForward = !isForward;
            stepLedProgressBar(true,isForward);
        }

        if (chooseButton.pressed() || confirmButton.pressed()) {
          state = MODE_SELECT;
          setLedsState(LEDS_AMOUNT, OFF);
        }
      }
      break;

    case MODE_SELECT: // Выбор режима
      if (chooseButton.pressed()) {
        gMode = (gMode+1) % MODES_AMOUNT;
        modeLedPin = LEDS_ARRAY[gMode];

        setLedsState(LEDS_AMOUNT());
        setLedState(modeLedPin, ON);
      }
      if (confirmButton.pressed()) {
        state = MODE_CONFIRM;
      }
      break;

    case MODE_CONFIRM: // Ожидание подтверждения режима
      BlinkOneLED(modeLedPin);
      setLedState(modeLedPin, OFF);
      
      state = AUTOSTART;
      break;

    case 3: // запуск режима
      if (gMode == 3) {
        if (!isTimerSelectionActivated) {
          AllLEDS(OFF);
          delay(LED_DELAY);
          AllLEDS(ON);
          delay(LED_DELAY);
          AllLEDS(OFF);
          isTimerSelectionActivated = true;
        }
        if (SelectTimeForTimer(timerSelectedPosition)) {
          choosenTimer = timerSelectedPosition+1;
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
            timer = millis() + choosenTimer * TEN_MINUTE_PERIOD;
            isTimerRunning = true;
          }
          if (TimerMode(timer, isTimerRunning)) {
            isTimerSelectionActivated = false;
            state = 0;
            break;
          }
          UpdateLedsForTimerMode(timer, choosenTimer);
          break;
    }
  }
}
