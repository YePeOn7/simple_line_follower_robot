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

// Fungsi khusus membaca nilai ADC sensor (Kiri & Kanan)
void bacaSensor(int &adcKiri, int &adcKanan) {
  adcKiri = analogRead(SENSOR_KIRI);
  adcKanan = analogRead(SENSOR_KANAN);
}

// Fungsi khusus mencetak nilai ADC ke Serial Monitor
void cetakSensor(int adcKiri, int adcKanan) {
  char buffer[60];
  snprintf(buffer, sizeof(buffer), "L (A0): %3d -- R (A1): %3d", adcKiri, adcKanan);
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

}
