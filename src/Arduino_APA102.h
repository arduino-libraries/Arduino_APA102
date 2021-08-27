/*
  This file is part of the Arduino_APA102 library.
  Copyright (c) 2020 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
    
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _Arduino_APA102_h
#define _Arduino_APA102_h

#include "Arduino.h"

class Arduino_APA102 {
public:
  Arduino_APA102(uint8_t numLEDs, uint8_t newDataPin, uint8_t newClockPin);
  ~Arduino_APA102();

  void begin(void);
  void end(void);

  void show(void);
  void clear(void);


  void setPixelColor(uint16_t indexLed, uint32_t newColor);
  void setPixelColor(uint16_t indexLed, uint8_t red, uint8_t green, uint8_t blue);
  void fill(uint32_t newColor , uint16_t startLed , uint16_t count );

  void setBrightness(uint8_t newBrightness);
  void setBrightness(uint8_t indexLed, uint8_t newBrightness);

  void setCurrent(uint8_t newCurrent);
  void setCurrent(uint8_t indexLed, uint8_t newCurrent);
  
  
  uint32_t Color(uint8_t newRed, uint8_t newGreen, uint8_t newBlue) {
    return (uint32_t)(newRed << 16 | newGreen << 8 | newBlue);
  }

  uint16_t getLeds(){
    return _numLeds;
  }

private:
  void writeBuffer(int index, uint8_t dataR, uint8_t dataG, uint8_t dataB, uint8_t dataBrightness, uint8_t dataCurrent);
  void _write8(uint8_t data);
  void _startFrame(void);
  void _endFrame(void);

  uint8_t _numLeds ;
  uint8_t _SCK_pin ;
  uint8_t _SDA_pin ;

  uint8_t *_pixel;	//5 bytes - R, G, B, Current, Btightness 
  
};

#endif