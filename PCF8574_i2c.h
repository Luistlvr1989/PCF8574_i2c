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

#ifndef PCF8574_I2C_H
#define PCF8574_I2C_H

#include "Wire.h"

#if ARDUINO >= 100
#include "Arduino.h"
#define I2CWRITE(x) Wire.write(x)
#define I2CREAD() Wire.read()
#else
#include "WProgram.h"
#define I2CWRITE(x) Wire.send(x)
#define I2CREAD() Wire.receive()
#endif

class PCF8574_I2C {
  private:
    uint8_t address;

    volatile byte readPins = 0;

    volatile byte writePins = 0;
  
    void updateGPIO();

    byte readGPIO();
  
  public:
    PCF8574_I2C(uint8_t address);

    void begin();

    void pinMode(uint8_t pin, uint8_t mode);

    uint8_t digitalRead(uint8_t pin);
};

#endif
