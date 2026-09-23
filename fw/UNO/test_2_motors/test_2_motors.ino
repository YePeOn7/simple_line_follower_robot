#include "Arduino.h"

// Right Motor Pins
#define PIN_RIGHT_PWM 5
#define PIN_RIGHT_DIR 4

// Left Motor Pins (Pin 6 as PWM, Pin 7 as DIR)
#define PIN_LEFT_PWM 6
#define PIN_LEFT_DIR 7

// Global raw speed state for left and right motors (-255 to 255)
int rawSpeedLeft = 0;
int rawSpeedRight = 0;

void readMotorDirInfo() {
  if (Serial.available() <= 0) return;

  String input = Serial.readStringUntil('\n');
  input.trim();
  if (input.length() == 0) return;

  int commaIndex = input.indexOf(',');
  if (commaIndex != -1) {
    String leftStr = input.substring(0, commaIndex);
    String rightStr = input.substring(commaIndex + 1);
    leftStr.trim();
    rightStr.trim();

    rawSpeedLeft = -constrain(leftStr.toInt(), -255, 255);
    rawSpeedRight = -constrain(rightStr.toInt(), -255, 255);

    Serial.print("Get Speed -> Left: ");
    Serial.print(rawSpeedLeft);
    Serial.print(", Right: ");
    Serial.println(rawSpeedRight);
  } else {
    int val = constrain(input.toInt(), -255, 255);
    rawSpeedLeft = -val;
    rawSpeedRight = -val;
    Serial.print("Get Speed -> Both: ");
    Serial.println(val);
  }
}


void setRightMotor(int speed) {
  if (speed >= 0) {
    digitalWrite(PIN_RIGHT_DIR, LOW); 
    analogWrite(PIN_RIGHT_PWM, speed);
  } else {
    digitalWrite(PIN_RIGHT_DIR, HIGH); 
    analogWrite(PIN_RIGHT_PWM, 255 + speed);
  }
}


void setLeftMotor(int speed) {
  if (speed >= 0) {
    digitalWrite(PIN_LEFT_DIR, LOW);
    analogWrite(PIN_LEFT_PWM, speed);
  } else {
    digitalWrite(PIN_LEFT_DIR, HIGH);
    analogWrite(PIN_LEFT_PWM, 255 + speed);
  }
}

void setup() {
  pinMode(PIN_RIGHT_PWM, OUTPUT);
  pinMode(PIN_RIGHT_DIR, OUTPUT);
  pinMode(PIN_LEFT_PWM, OUTPUT);
  pinMode(PIN_LEFT_DIR, OUTPUT);

  Serial.begin(115200);
  Serial.println("--- Dual Motor PWM Control Test ---");

  setLeftMotor(0);
  setRightMotor(0);
}

void loop() {
  readMotorDirInfo();
  setLeftMotor(rawSpeedLeft);
  setRightMotor(rawSpeedRight);
}

