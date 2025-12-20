
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

unsigned long timerModePeriod = 0;

bool isTimerSelectionActivated = false;
bool isTimerRunning = false;

Button chooseButton(CHOOSE_BTN);
Button confirmButton(CONFIRM_BTN);

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

  confirmButton.begin();
  chooseButton.begin();

}

void loop() {
  switch (state) {
    case WAIT_INPUT: // Ожидание нажатия кнопки
      static bool isForward = true;

      if (millisTimer(WAITING_ANIMATION_INTERVAL_MS)) {
        if (stepLedProgressBar(false,isForward)) {
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

        setLedsState(LEDS_AMOUNT, OFF);
        setLedState(modeLedPin, ON);
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
    break;
}
