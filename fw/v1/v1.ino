// Pin Mapping
const int SENSOR_LEFT = A0;
const int SENSOR_RIGHT = A1;

const int MOTOR_RIGHT_IN1 = 4;
const int MOTOR_RIGHT_IN2 = 5;

const int MOTOR_LEFT_IN1 = 6;
const int MOTOR_LEFT_IN2 = 7;

void stopMotors() {
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi pin motor sebagai OUTPUT
  pinMode(MOTOR_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN2, OUTPUT);
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);

  // Pastikan motor berhenti di awal
  stopMotors();
}

void readAndPrintSensors(const char* actionName) {
  int valueA0 = analogRead(SENSOR_LEFT);
  int valueA1 = analogRead(SENSOR_RIGHT);

  float voltageA0 = valueA0 * (5.0 / 1023.0);
  float voltageA1 = valueA1 * (5.0 / 1023.0);

  char voltA0Str[6], voltA1Str[6];
  dtostrf(voltageA0, 4, 2, voltA0Str);
  dtostrf(voltageA1, 4, 2, voltA1Str);

  char buffer[100];
  snprintf(buffer, sizeof(buffer), "[%-12s] L (A0): %3d (%s V) -- R (A1): %3d (%s V)",
           actionName, valueA0, voltA0Str, valueA1, voltA1Str);
  Serial.println(buffer);
}

void rightMotorForward() {
  digitalWrite(MOTOR_RIGHT_IN1, HIGH);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void rightMotorBackward() {
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}

void leftMotorForward() {
  digitalWrite(MOTOR_LEFT_IN1, HIGH);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
}

void leftMotorBackward() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, HIGH);
}

void loop() {
  // === Sekuens 1: Motor Kanan Maju ===
  rightMotorForward();
  for (int i = 0; i < 10; i++) {
    readAndPrintSensors("Kanan Maju");
    delay(100);
  }
  stopMotors();
  delay(500);

  // === Sekuens 2: Motor Kanan Mundur ===
  rightMotorBackward();
  for (int i = 0; i < 10; i++) {
    readAndPrintSensors("Kanan Mundur");
    delay(100);
  }
  stopMotors();
  delay(500);

  // === Sekuens 3: Motor Kiri Maju ===
  leftMotorForward();
  for (int i = 0; i < 10; i++) {
    readAndPrintSensors("Kiri Maju");
    delay(100);
  }
  stopMotors();
  delay(500);

  // === Sekuens 4: Motor Kiri Mundur ===
  leftMotorBackward();
  for (int i = 0; i < 10; i++) {
    readAndPrintSensors("Kiri Mundur");
    delay(100);
  }
  stopMotors();
  delay(1000);
}
