// Pin Mapping
const int SENSOR_KIRI = A0;
const int SENSOR_KANAN = A1;

const int MOTOR_KANAN_IN1 = 4;
const int MOTOR_KANAN_IN2 = 5;

const int MOTOR_KIRI_IN1 = 6;
const int MOTOR_KIRI_IN2 = 7;

// Threshold Sensor (Ambang Batas)
#define THRESHOLD_SENSOR_KIRI  500
#define THRESHOLD_SENSOR_KANAN 500

// Variable Global Sensor (ADC & Logic Boolean)
int adcSensorKiri = 0;
int adcSensorKanan = 0;

bool logicSensorKiri = false;
bool logicSensorKanan = false;

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
void robotGerak(int lin, int rot) {
  int kecepatanKiri = lin + rot;
  int kecepatanKanan = lin - rot;

  setMotorKiri(kecepatanKiri);
  setMotorKanan(kecepatanKanan);
}

// Membaca nilai ADC dan mengonversi ke logika boolean berdasarkan threshold
void bacaSensor() {
  adcSensorKiri = analogRead(SENSOR_KIRI);
  adcSensorKanan = analogRead(SENSOR_KANAN);

  logicSensorKiri = (adcSensorKiri > THRESHOLD_SENSOR_KIRI);
  logicSensorKanan = (adcSensorKanan > THRESHOLD_SENSOR_KANAN);
}

// Mencetak data sensor (ADC & Logic) ke Serial Monitor
void cetakSensor() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer), "L (A0): %3d [%d] -- R (A1): %3d [%d]",
           adcSensorKiri, logicSensorKiri, adcSensorKanan, logicSensorKanan);
  Serial.println(buffer);
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi pin motor sebagai OUTPUT
  pinMode(MOTOR_KANAN_IN1, OUTPUT);
  pinMode(MOTOR_KANAN_IN2, OUTPUT);
  pinMode(MOTOR_KIRI_IN1, OUTPUT);
  pinMode(MOTOR_KIRI_IN2, OUTPUT);

  // Hentikan motor di awal dengan robotGerak(0, 0)
  robotGerak(0, 0);
}

void loop() {
  // Baca data sensor ADC & logika boolean
//   bacaSensor();

  // Cetak status sensor ke Serial Monitor
//   cetakSensor();

  // Logika Gerakan Motor:
  // Motor maju jika sensor mendeteksi permukaan putih (true), sebaliknya mundur (-100)
//   int speedKiri = logicSensorKiri ? 100 : -100;
//   int speedKanan = logicSensorKanan ? 100 : -100;

//   setMotorKiri(speedKiri);
//   setMotorKanan(speedKanan);

//   delay(100);
}
