#include "Arduino.h"
#include "Wire.h"
#include "PCF8574_i2c.h"

const int pcfAddress = 0x38;
PCF8574_I2C pcf8574(0x38);

void setup() {
  Serial.begin(9600);

  pcf8574.begin();
  pcf8574.pinMode(0, OUTPUT);
  pcf8574.pinMode(7, INPUT);
}
 
void loop() {
  uint8_t value = pcf8574.digitalRead(0);
  Serial.println(value);
  
  value = pcf8574.digitalRead(7);
  Serial.println(value);

  delay(2000);
}
