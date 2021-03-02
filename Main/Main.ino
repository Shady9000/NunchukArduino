void setup() {
  Serial.begin(9600);
  wireSetup();
}

void loop() {
  updateArduino();
  debugNunchuk();
}
