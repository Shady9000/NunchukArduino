#include <Wire.h>;
const byte ADDRESS = 0x52;
const byte INIT_DATA1 = 0x55;
const byte INIT_DATA2 = 0x00;
const int INIT_LOCATIE1 = 0xA400F0;
const int INIT_LOCATIE2 = 0xA400FB;
const byte END_BYTE = 0x00;

int analogX;
int analogY;
int acclX;
int acclY;
int acclZ;
int zButton;
int cButton;

void debugNunchuk() {
  Serial.print("X: ");
  Serial.print(analogX, DEC);
  Serial.print(" ");
  Serial.print("Y: ");
  Serial.print(analogY, DEC);
  Serial.print(" ");
  Serial.print("waarde: ");
  Serial.print(zButton);
  Serial.print(" ");
  Serial.print("acclX: ");
  Serial.print(acclX);
  Serial.print(" ");
  Serial.print("acclY: ");
  Serial.print(acclY);
  Serial.print(" ");
  Serial.print("acclZ: ");
  Serial.print(acclZ);
  Serial.println(" ");
}

void wireSetup() {
  Wire.begin();
  sendData(INIT_DATA1, INIT_LOCATIE1);
  sendData(INIT_DATA2, INIT_LOCATIE2);
}

void updateArduino() {
  int index = 0;
  int waardenArray[6];

  Wire.requestFrom(ADDRESS, 6);
  while (Wire.available()) {
    waardenArray[index] = Wire.read();
    index++;
  }

  analogX = waardenArray[0];
  analogY = waardenArray[1];
  zButton = !((waardenArray[5] >> 0) & 1);
  cButton = !((waardenArray[5] >> 1) & 1);
  acclX = (waardenArray[2] << 2) | (waardenArray[5] >> 2);
  acclY = (waardenArray[3] << 2) | (waardenArray[5] >> 4);
  acclZ = (waardenArray[4] << 2) | (waardenArray[5] >> 6);

  sendData(END_BYTE, END_BYTE);
}

void sendData(byte data, byte locatie) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(locatie);
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}
