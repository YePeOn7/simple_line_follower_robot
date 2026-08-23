// Pin Mapping
const int SENSOR_KIRI = A0;
const int SENSOR_KANAN = A1;

const int MOTOR_KANAN_IN1 = 4;
const int MOTOR_KANAN_IN2 = 5;

const int MOTOR_KIRI_IN1 = 6;
const int MOTOR_KIRI_IN2 = 7;

void stopMotor() {
  digitalWrite(MOTOR_KANAN_IN1, LOW);
  digitalWrite(MOTOR_KANAN_IN2, LOW);
  digitalWrite(MOTOR_KIRI_IN1, LOW);
  digitalWrite(MOTOR_KIRI_IN2, LOW);
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi pin motor sebagai OUTPUT
  pinMode(MOTOR_KANAN_IN1, OUTPUT);
  pinMode(MOTOR_KANAN_IN2, OUTPUT);
  pinMode(MOTOR_KIRI_IN1, OUTPUT);
  pinMode(MOTOR_KIRI_IN2, OUTPUT);

  // Pastikan motor berhenti di awal
  stopMotor();
}

void bacaDanCetakSensor(const char* namaAksi) {
  int valueA0 = analogRead(SENSOR_KIRI);
  int valueA1 = analogRead(SENSOR_KANAN);

  float voltageA0 = valueA0 * (5.0 / 1023.0);
  float voltageA1 = valueA1 * (5.0 / 1023.0);

  char voltA0Str[6], voltA1Str[6];
  dtostrf(voltageA0, 4, 2, voltA0Str);
  dtostrf(voltageA1, 4, 2, voltA1Str);

  char buffer[100];
  snprintf(buffer, sizeof(buffer), "[%-12s] L (A0): %3d (%s V) -- R (A1): %3d (%s V)",
           namaAksi, valueA0, voltA0Str, valueA1, voltA1Str);
  Serial.println(buffer);
}

void setMotorKanan(int kecepatan) {
  kecepatan = constrain(kecepatan, -255, 255);
  if (kecepatan > 0) {
    digitalWrite(MOTOR_KANAN_IN1, LOW);
    analogWrite(MOTOR_KANAN_IN2, kecepatan);
  } else if (kecepatan < 0) {
    digitalWrite(MOTOR_KANAN_IN1, HIGH);
    analogWrite(MOTOR_KANAN_IN2, 255 + kecepatan); // kecepatan bernilai negatif
  } else {
    digitalWrite(MOTOR_KANAN_IN1, LOW);
    digitalWrite(MOTOR_KANAN_IN2, LOW);
  }
}

void setMotorKiri(int kecepatan) {
  kecepatan = constrain(kecepatan, -255, 255);
  if (kecepatan > 0) {
    digitalWrite(MOTOR_KIRI_IN2, LOW);
    analogWrite(MOTOR_KIRI_IN1, kecepatan);
  } else if (kecepatan < 0) {
    digitalWrite(MOTOR_KIRI_IN2, HIGH);
    analogWrite(MOTOR_KIRI_IN1, 255 + kecepatan); // kecepatan bernilai negatif
  } else {
    digitalWrite(MOTOR_KIRI_IN1, LOW);
    digitalWrite(MOTOR_KIRI_IN2, LOW);
  }
}

// Konversi linier (lin) & rotasi (rot) ke gerakan roda diferensial
// lin: -255 (mundur penuh) s/d 255 (maju penuh)
// rot: -255 (putar kiri) s/d 255 (putar kanan)
void robot_gerak(int lin, int rot) {
  int kecepatanKiri = lin + rot;
  int kecepatanKanan = lin - rot;

  setMotorKiri(kecepatanKiri);
  setMotorKanan(kecepatanKanan);
}

void loop() {
  // === Sekuens 1: Maju (lin: 200, rot: 0) ===
  robot_gerak(200, 0);
  for (int i = 0; i < 10; i++) {
    bacaDanCetakSensor("Maju");
    delay(100);
  }
  robot_gerak(0, 0);
  delay(500);

  // === Sekuens 2: Mundur (lin: -200, rot: 0) ===
  robot_gerak(-200, 0);
  for (int i = 0; i < 10; i++) {
    bacaDanCetakSensor("Mundur");
    delay(100);
  }
  robot_gerak(0, 0);
  delay(500);

  // === Sekuens 3: Putar Kanan (lin: 0, rot: 200) ===
  robot_gerak(0, 200);
  for (int i = 0; i < 10; i++) {
    bacaDanCetakSensor("Putar Kanan");
    delay(100);
  }
  robot_gerak(0, 0);
  delay(500);

  // === Sekuens 4: Putar Kiri (lin: 0, rot: -200) ===
  robot_gerak(0, -200);
  for (int i = 0; i < 10; i++) {
    bacaDanCetakSensor("Putar Kiri");
    delay(100);
  }
  robot_gerak(0, 0);
  delay(1000);
}
