#include "Arduino.h"

#define PIN_MOTOR 5 //pwm
#define PIN_DIR 4

// Global raw speed state (-255 to 255)
int rawSpeed = 0;

// Reads serial input and extracts the raw integer speed
void readMotorSpeedInfo() {
  if (Serial.available() <= 0) return;

  String input = Serial.readStringUntil('\n');
  input.trim();
  if (input.length() == 0) return;

  rawSpeed = constrain(input.toInt(), -255, 255);

  Serial.print("Get Speed: ");
  Serial.println(rawSpeed);
}

// Responsible for motor control logic & setting hardware pins
void updateMotor(int speed) {
  if (speed >= 0) {
    digitalWrite(PIN_DIR, LOW); // Clockwise (CW)
    analogWrite(PIN_MOTOR, speed);
  } else {
    digitalWrite(PIN_DIR, HIGH);  // Counter-Clockwise (CCW - inverted PWM)
    analogWrite(PIN_MOTOR, 255 + speed);
  }
}

void setup() {
  pinMode(PIN_DIR, OUTPUT);

  Serial.begin(115200);
  Serial.println("--- Motor Control PWM Test ---");

  updateMotor(0);
}

void loop() {
  readMotorSpeedInfo();
  updateMotor(rawSpeed);
}


