
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

GameMode gMode = NONE;

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

  pinMode(MODE_BTN, INPUT);
  pinMode(TIMER_BTN, INPUT);

  Serial.begin(9600);

  StartAnimation();
}

void loop() {
  delay(50);
  if (digitalRead(MODE_BTN) == 1) {
    gMode = static_cast<GameMode>((gMode + 1) % 5);
  }
  switch (gMode) {
    case NONE:
      Serial.println("NONE");
      AllLEDS(LED_OFF);
      digitalWrite(0, 1);
    case BASE:
      Serial.println("BASE");
      AllLEDS(LED_OFF);
      digitalWrite(1, 1);
    case SIREN_ONLY:
      Serial.println("SIREN_ONLY");
      AllLEDS(LED_OFF);
      digitalWrite(2, 1);
    case IGNITER_ONLY:
      Serial.println("IGNITER_ONLY");
      AllLEDS(LED_OFF);
      digitalWrite(3, 1);
    case TIMER:
      Serial.println("TIMER");
      AllLEDS(LED_OFF);
      digitalWrite(4, 1);
  }
}
