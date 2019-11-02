#include "Arduino.h"
#include "Wire.h"
#include "PCF8574_i2c.h"

PCF8574_I2C pcf8574(0x38);

unsigned long prevMillis = millis();
uint8_t test = LOW;

void setup() {
  Serial.begin(9600);

  pcf8574.begin();
  pcf8574.pinMode(0, INPUT);
  pcf8574.pinMode(7, INPUT);
}
 
void loop() {
  uint8_t value = pcf8574.digitalRead(0);
  Serial.println(value);
  
  value = pcf8574.digitalRead(7);
  Serial.println(value);

  delay(2000);

  if (millis() > prevMillis + 5000) {
    pcf8574.digitalWrite(0, test);
    pcf8574.digitalWrite(7, test);
  
    if (test == LOW) 
      test = HIGH;
    else 
      test = LOW;

    prevMillis = millis();
  }
}
