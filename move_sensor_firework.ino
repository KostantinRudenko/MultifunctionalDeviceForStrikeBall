
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
      
      if (digitalRead(MODE_BTN) == 0) {
        gMode = (gMode+1) % 4;
        modeLedPin = gMode;
        timer = millis() + CONFIRM_TIME;
        isTimerRunning = true;
        isWaitingForActivation = false;
      }
      AllLEDS(LED_OFF);
      digitalWrite(modeLedPin, LED_ON);
      delay(BUTTON_DELAY);
      state = 1;

    case 1:

      if (isTimerRunning && !isModeActivated) {
        if (millis() > timer){
        isTimerRunning = false;
        isWaitingForActivation = true;
        
        BlinkOneLED(modeLedPin);
        delay(LED_DELAY);
        digitalWrite(modeLedPin, LED_OFF);
        
        state = 2;
        break;
        }
      }
      state = 0;

    case 2:

      if (digitalRead(MODE_BTN) == 0) {
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

        case 1: // Basic
          break;  
        case 2:
          break;
        case 3:
          break;
        case 4:
          break;
      }
  }
}
