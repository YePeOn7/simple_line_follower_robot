void setup() {
  Serial.begin(115200);
}

void loop() {
  int valueA0 = analogRead(A0);
  int valueA1 = analogRead(A1);

  float voltageA0 = valueA0 * (5.0 / 1023.0);
  float voltageA1 = valueA1 * (5.0 / 1023.0);

  char voltA0Str[6], voltA1Str[6];
  dtostrf(voltageA0, 4, 2, voltA0Str);
  dtostrf(voltageA1, 4, 2, voltA1Str);

  char buffer[80];
  snprintf(buffer, sizeof(buffer), "L (A0): %3d (%s V) -- R (A1): %3d (%s V)", valueA0, voltA0Str, valueA1, voltA1Str);
  Serial.println(buffer);
}
