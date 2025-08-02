
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

/* ---------- Режими ----------
 * 1 - Базовый режим (сирена + зажигатель)
 * 2 - Режим только сирены
 * 3 - Режим только зажигателя
 * 4 - Таймер с зажигателям
 * Номер светодиода соответствует номеру режима modeLedPin=gMode
 * ---------------------------- */

uint8_t state = 0;
uint8_t gMode = 0;
uint8_t modeLedPin = gMode;

unsigned long timer = 0;

bool isTimerRunning = false;
bool isWaitingForActivation = false;
bool isModeActivated = false;

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
  switch (state) {
    
    case 0:
      
      if (digitalRead(MODE_BTN) == BUTTON_CLICKED) {
        gMode = (gMode+1) % MODES_AMOUNT;
        modeLedPin = gMode;
        timer = millis() + CONFIRM_TIME;
        isTimerRunning = true;
        isWaitingForActivation = false;
      }
      AllLEDS(OFF);
      digitalWrite(modeLedPin, ON);
      delay(BUTTON_DELAY);
      state = 1;

    case 1:

      if (isTimerRunning && !isModeActivated) {
        if (millis() > timer){
        isTimerRunning = false;
        isWaitingForActivation = true;
        
        BlinkOneLED(modeLedPin);
        delay(LED_DELAY);
        digitalWrite(modeLedPin, OFF);
        
        state = 2;
        break;
        }
      }
      state = 0;

    case 2:

      if (digitalRead(MODE_BTN) == BUTTON_CLICKED) {
        isWaitingForActivation = false;
        AutostartAnimation();
        isModeActivated = true;
        state = 3;
        break;
      }
      delay(BUTTON_DELAY);
      break;
  
    case 3:

      switch (gMode) {

        case 1:
          BasicMode();
          break;
        case 2:
          OnlySirenMode();
          break;
        case 3:
          OnlyIgniterMode();
          break;
        case 4:
          if (!isTimerRunning){
            timer = millis();
          }
          TimerMode(timer, isTimerRunning);
          break;
      }
  }
}
