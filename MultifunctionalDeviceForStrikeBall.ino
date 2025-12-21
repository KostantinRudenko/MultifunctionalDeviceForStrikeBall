
#pragma region ______________________________ Includes

#include "global.h"
#include "button.h"
#include "device.h"
#include "functions.h"
#include "animations.h"

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

unsigned long timerModePeriod = 0;

Button chooseButton(CHOOSE_BTN);
Button confirmButton(CONFIRM_BTN);

InputDevice PIRSensor(PIR_SENSOR_PIN);
OutputDevice Siren(SIREN_PIN);
OutputDevice Igniter(IGNITER_PIN);

#pragma endregion Variables

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(LED_PIN_6, OUTPUT);

  PIRSensor.begin();
  Siren.begin();
  Igniter.begin();

  confirmButton.begin();
  chooseButton.begin();

}

static bool isForward = true;
void loop() {
  switch (state) {
    case WAIT_INPUT: // Ожидание нажатия кнопки

      if (millisTimer(WAITING_ANIMATION_INTERVAL_MS)) {
        if (stepLedProgressBar(false,isForward)) {
            isForward = !isForward;
            stepLedProgressBar(true,isForward);
        }
      }
      if (chooseButton.pressed() || confirmButton.pressed()) {
        state = MODE_SELECT;
        setLedsState(LEDS_AMOUNT, OFF);
      }
      break;

    case MODE_SELECT: // Выбор режима
      if (chooseButton.pressed()) {
        gMode = (gMode+1) % GAMEMODES_AMOUNT;

        setLedsState(LEDS_AMOUNT, OFF);
        setLedState(LEDS_ARRAY[gMode], ON);
      }
      if (confirmButton.pressed()) {
        state = MODE_CONFIRM;
      }
      break;

    case MODE_CONFIRM: // Ожидание подтверждения режима
      if (confirmAnimation()) {
        if (gMode == TIMER_MODE) 
          state = TIMER_SELECTION;
        else
          state = AUTOSTART;
      }
      break;

    case TIMER_SELECTION:
      if (chooseButton.pressed()) {
        timerSelectedPosition = (timerSelectedPosition+1)%TIMER_SELECT_AMOUNT;
        setLedsState(LEDS_AMOUNT, OFF);
        setLedState(LEDS_ARRAY[timerSelectedPosition], ON);
      }

      if (confirmButton.pressed()) {
        state = TIMER_CONFIRM;
      }
      break;
    
    case TIMER_CONFIRM:
      if (confirmAnimation()) {
        timerModePeriod = (timerSelectedPosition+1)*TIMER_PERIOD;
        state = AUTOSTART;
      }
      break;

    case AUTOSTART: // запуск режима
      if (autostartAnimation()) {
        state = RUNNING;
      }
      break;
  
    case RUNNING: // Выбор и работа игрового режима
      switch (gMode) {
        case BASE_MODE:
          if (BasicMode(PIRSensor, Siren, Igniter)) {
            Siren.resetDevice();
            Igniter.resetDevice();
            state = WAIT_INPUT;
          }
          break;
        case SIREN_ONLY_MODE:
          if (OnlySirenMode(PIRSensor, Siren) {
              Siren.resetDevice();
              state = WAIT_INPUT;
            }
          break;
        case IGNITER_ONLY_MODE:
          if (OnlyIgniterMode(PIRSensor, Igniter) {
              Igniter.resetDevice();
              state = WAIT_INPUT;
            }
          break;
        case TIMER_MODE:
          if (TimerMode(timerModePeriod, Igniter)) {
            Igniter.resetDevice();
            timerSelectedPosition = 0;
            timerModePeriod = 0;
            state = WAIT_INPUT;
          }
          break;
      
      }
    break;
  }
}
