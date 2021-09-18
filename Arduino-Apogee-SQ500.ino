#include <Wire.h>

void setup() {
  Wire.begin(); // Initiate the Wire library
  Serial.begin(9600);
  delay(100);

 // delay(5000);
  Serial.println();
  Serial.print("Setup SQ500");
  SetupSQ500();
  Serial.print("Setup complete");
}

void loop() {
  Serial.println();
  Serial.print("Reading sensor: ");
  Serial.print(ReadSQ500());
  Serial.println();
  delay(3000);

}

void SetupSQ500() {
  Wire.beginTransmission(0x68);
  Wire.write(1 << 4 | 1 << 7 | 1 << 3);
  Wire.endTransmission(); 
}

float ReadSQ500() {
  int16_t result = 0;
  uint8_t msb;
  uint8_t lsb;

  Wire.requestFrom(0x68,3); // Request the transmitted two bytes from the two registers
  if(Wire.available()<=3) {  // 
    msb = Wire.read();
    lsb = Wire.read();
    uint8_t config = Wire.read();
    Serial.print(msb, HEX);
    Serial.print(lsb, HEX);
    Serial.println();
  }

  result = msb << 8 | lsb;
  if (result < 0)
    result = 0;

  float ret = 0;

  ret = (result / (float)0xFFFF) *  2.048;
  ret *= 2000;
  
  return ret;
}
