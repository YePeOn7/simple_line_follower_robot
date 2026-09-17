#include "Arduino.h"

#define PIN_MOTOR_L 5
#define PIN_MOTOR_R 6

int speedL = 0;
int speedR = 0;

void applySpeeds(int l, int r) {
  speedL = constrain(l, 0, 255);
  speedR = constrain(r, 0, 255);

  analogWrite(PIN_MOTOR_L, speedL);
  analogWrite(PIN_MOTOR_R, speedR);

  Serial.print("Set -> Motor L: ");
  Serial.print(speedL);
  Serial.print(" | Motor R: ");
  Serial.println(speedR);
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100); // 100ms timeout for fast parsing response
  Serial.println("--- Motor Control Serial Interface ---");
  Serial.println("Format: <speedL>,<speedR> (e.g. 100,100)");
  applySpeeds(0, 0);
}

void loop() {
  if (Serial.available() > 0) {
    int l = Serial.parseInt();
    int r = Serial.parseInt();

    // Consume any leftover newline/carriage return characters
    while (Serial.available() > 0 && (Serial.peek() == '\n' || Serial.peek() == '\r')) {
      Serial.read();
    }

    applySpeeds(l, r);
  }
}



