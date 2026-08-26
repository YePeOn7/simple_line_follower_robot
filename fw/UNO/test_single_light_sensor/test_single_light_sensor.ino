void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(A0);
  float voltage = value * (5.0 / 1023.0);

  char voltStr[6];
  dtostrf(voltage, 4, 2, voltStr);

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "ADC: %3d\tVoltage: %s V", value, voltStr);
  Serial.println(buffer);
}

