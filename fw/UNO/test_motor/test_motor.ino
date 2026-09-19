#include "Arduino.h"

#define PIN_A 4
#define PIN_B 5

int motorDir = 0;

void readMotorDirInfo() {
  if (Serial.available() <= 0) return;

  String input = Serial.readStringUntil('\n');
  input.trim();
  if (input.length() == 0) return;

  int val = input.toInt();
  if (val == -1 || val == 0 || val == 1) {
    if (val == 0 && input != "0") return;

    motorDir = val;
    Serial.print("Get Command: ");
    Serial.print(motorDir);
    if (motorDir == -1) {
      Serial.println(" (CCW)");
    } else if (motorDir == 1) {
      Serial.println(" (CW)");
    } else {
      Serial.println(" (STOP)");
    }
  }
}

// Responsible for digital logic motor control & setting hardware pins (without PWM)
void updateMotor(int dir) {
  if (dir == 1) {
    digitalWrite(PIN_A, HIGH);  // Clockwise (CW)
    digitalWrite(PIN_B, LOW);
  } else if (dir == -1) {
    digitalWrite(PIN_A, LOW);   // Counter-Clockwise (CCW)
    digitalWrite(PIN_B, HIGH);
  } else {
    digitalWrite(PIN_A, LOW);   // Stop
    digitalWrite(PIN_B, LOW);
  }
}

void setup() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  Serial.begin(115200);
  Serial.println("--- Motor Test ---");

  updateMotor(motorDir);
}

void loop() {
  readMotorDirInfo(); // baca data serial
  updateMotor(motorDir);
}
