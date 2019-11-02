/*
 * PCF8574 GPIO Ports Expansor
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Luis Talavera All right reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "PCF8574_i2c.h"
#include "Wire.h"

PCF8574_I2C::PCF8574_I2C(uint8_t address) {
  this->address = address;
}

void PCF8574_I2C::begin() {
  Wire.begin();
  updateGPIO();
}

void PCF8574_I2C::pinMode(uint8_t pin, uint8_t mode) {
  switch (mode) {
    case INPUT:
      readPins |= bit(pin);
      writePins &= ~bit(pin);
      break;
  
    case OUTPUT:
      readPins &= ~bit(pin);
      writePins |= bit(pin);
      break;
  }

  updateGPIO();
}

void PCF8574_I2C::updateGPIO() {
  uint8_t pinsInUse = readPins | writePins;

  Wire.beginTransmission(address);
  I2CWRITE(pinsInUse);
  Wire.endTransmission();
}

uint8_t PCF8574_I2C::digitalRead(uint8_t pin) {
  byte value = readGPIO();
  return (value & bit(pin)) ? HIGH : LOW;
}

byte PCF8574_I2C::readGPIO() {
  byte value = 0;
  Wire.requestFrom(address, (uint8_t) 1);
  
  if (Wire.available()) {
    value = I2CREAD();
  }

  return value;
}

void PCF8574_I2C::digitalWrite(uint8_t pin, uint8_t value) {
  byte write = writePins & bit(pin);
  
  if (value) {
    writePins |= write;
  } else {
    writePins &= ~write;
  }

  updateGPIO();
}
