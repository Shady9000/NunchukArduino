#include <Wire.h>;
const byte ADDRESS = 0x52;
const byte INIT_DATA1 = 0x55;
const byte INIT_DATA2 = 0x00;
const int INIT_LOCATIE1 = 0xA400F0;
const int INIT_LOCATIE2 = 0xA400FB;
const byte END_BYTE = 0x00;

int input[7];

void debugNunchuk() {
  Serial.print("X: ");
  Serial.print(input[0], DEC);
  Serial.print(" ");
  Serial.print("Y: ");
  Serial.print(input[1], DEC);
  Serial.print(" ");
  Serial.print("Z: ");
  Serial.print(input[2]);
  Serial.print(" ");
  Serial.print("C: ");
  Serial.print(input[3]);
  Serial.print(" ");
  Serial.print("acclX: ");
  Serial.print(input[4]);
  Serial.print(" ");
  Serial.print("acclY: ");
  Serial.print(input[5]);
  Serial.print(" ");
  Serial.print("acclZ: ");
  Serial.print(input[6]);
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
  //joyX
  input[0] = waardenArray[0];
  //joyY
  input[1] = waardenArray[1];
  //btnZ
  input[2] = !((waardenArray[5] >> 0) & 1);
  //btnC
  input[3] = !((waardenArray[5] >> 1) & 1);
  //acclX
  input[4] = (waardenArray[2] << 2) | (waardenArray[5] >> 2);
  //acclY
  input[5] = (waardenArray[3] << 2) | (waardenArray[5] >> 4);
  //acclz
  input[6] = (waardenArray[4] << 2) | (waardenArray[5] >> 6);

  sendData(END_BYTE, END_BYTE);

  return output;
}

void sendData(byte data, byte locatie) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(locatie);
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}
