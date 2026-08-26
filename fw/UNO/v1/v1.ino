// Pin Mapping
const int SENSOR_KIRI = A0;
const int SENSOR_KANAN = A1;

const int MOTOR_KANAN_IN1 = 4;
const int MOTOR_KANAN_IN2 = 5;

const int MOTOR_KIRI_IN1 = 6;
const int MOTOR_KIRI_IN2 = 7;

#define MODE 0 // 0: Line Tracking Normal, 1: Telusur Kanan, 2: Telusur Kiri

#define KECEPATAN 170
#define KECEPATAN_BELOK 120

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
  if (kecepatan >= 0) {
    digitalWrite(MOTOR_KANAN_IN1, LOW);
    analogWrite(MOTOR_KANAN_IN2, kecepatan);
  } else {
    digitalWrite(MOTOR_KANAN_IN1, HIGH);
    analogWrite(MOTOR_KANAN_IN2, 255 + kecepatan); // kecepatan bernilai negatif
  }
}

void setMotorKiri(int kecepatan) {
  kecepatan = constrain(kecepatan, -255, 255);
  if (kecepatan >= 0) {
    digitalWrite(MOTOR_KIRI_IN2, HIGH);
    analogWrite(MOTOR_KIRI_IN1, 255 - kecepatan);
  } else {
    digitalWrite(MOTOR_KIRI_IN2, LOW);
    analogWrite(MOTOR_KIRI_IN1, -kecepatan); // -kecepatan bernilai positif
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
  bacaSensor();
  // cetakSensor();

  int speedKiri = 0;
  int speedKanan = 0;

#if MODE == 0
  // Mode 0: Dual-Sensor Line Tracking biasa
  // Jika logic sensor SAMA -> Pakai KECEPATAN, jika BEDA -> Pakai KECEPATAN_BELOK
  int kecepatan = (logicSensorKiri == logicSensorKanan) ? KECEPATAN : KECEPATAN_BELOK;
  speedKiri  = logicSensorKiri  ? kecepatan : -kecepatan;
  speedKanan = logicSensorKanan ? kecepatan : -kecepatan;

#elif MODE == 1
  // Mode 1: Telusur Kanan
  // Jika logic sensor BEDA -> Pakai KECEPATAN, jika SAMA -> Pakai KECEPATAN_BELOK
  int kecepatan = (logicSensorKiri != logicSensorKanan) ? KECEPATAN : KECEPATAN_BELOK;
  speedKiri  = (!logicSensorKiri) ? kecepatan : -kecepatan;
  speedKanan = logicSensorKanan   ? kecepatan : -kecepatan;

#elif MODE == 2
  // Mode 2: Telusur Kiri (Kebalikan Mode 1)
  // Jika logic sensor BEDA -> Pakai KECEPATAN, jika SAMA -> Pakai KECEPATAN_BELOK
  int kecepatan = (logicSensorKiri != logicSensorKanan) ? KECEPATAN : KECEPATAN_BELOK;
  speedKiri  = logicSensorKiri    ? kecepatan : -kecepatan;
  speedKanan = (!logicSensorKanan) ? kecepatan : -kecepatan;
#endif

  setMotorKiri(speedKiri);
  setMotorKanan(speedKanan);

//   delay(100);
}
