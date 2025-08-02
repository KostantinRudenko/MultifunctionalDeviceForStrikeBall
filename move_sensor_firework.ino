
#pragma region ______________________________ Includes

#include "global.h"
#include "functions.h"

#pragma endregion Includes

#pragma region ______________________________ Variables

//GameMode gMode = NONE;
int gMode = 0;
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

  Serial.begin(9600);
  Serial.println("INITIALIZED");

  StartAnimation();
}

void loop() {
  if (digitalRead(MODE_BTN) == 0) {
    //delay(100)
    //if (digitalRead(MODE_BTN) == 1){
        Serial.println("Changing...");
        gMode = (gMode+1) % 5;
        Serial.print("Mode: ");
        Serial.println(gMode);
      //}
  }
  switch (gMode) {
    case 0:
      Serial.println("NONE");
      AllLEDS(LED_OFF);
      digitalWrite(0, 1);
    case 1:
      Serial.println("BASE");
      AllLEDS(LED_OFF);
      digitalWrite(1, 1);
    case 2:
      Serial.println("SIREN_ONLY");
      AllLEDS(LED_OFF);
      digitalWrite(2, 1);
    case 3:
      Serial.println("IGNITER_ONLY");
      AllLEDS(LED_OFF);
      digitalWrite(3, 1);
    case 4:
      Serial.println("TIMER");
      AllLEDS(LED_OFF);
      digitalWrite(4, 1);
  }
  delay(250);
}
