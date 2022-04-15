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

#include "Arduino_APA102.h"

#include <Arduino.h>

#define LED_FRAME_RED(indexLed)(_numLeds * indexLed)
#define LED_FRAME_GREEN(indexLed)((_numLeds * indexLed) +1)
#define LED_FRAME_BLUE(indexLed)((_numLeds * indexLed) + 2)
#define LED_FRAME_BRIGHTNESS(indexLed)((_numLeds * indexLed) + 3)
#define LED_FRAME_CURRENT(indexLed)((_numLeds * indexLed) + 4)
#define LED_FRAME_FULL(indexLed)(indexLed * 5)

Arduino_APA102::Arduino_APA102(uint8_t newNumLeds, uint8_t newDataPin, uint8_t newClockPin){
  free(_led);

  uint16_t n = newNumLeds;
  _numLeds = newNumLeds;
  _SDA_pin = newDataPin;
  _SCK_pin = newClockPin;

  uint16_t bytes = n * 5; // R,G,B, Bright, Current

  if ((_led = (uint8_t *)malloc(bytes))){
    _numLeds = n;
    memset(_led, 0,  LED_FRAME_FULL(_numLeds));
  }
}

void Arduino_APA102::writeBuffer(int index, uint8_t dataR, uint8_t dataG, uint8_t dataB, uint8_t dataBrightness, uint8_t dataCurrent){
  int n = 0;
  _led[LED_FRAME_RED(index)] = dataR;
  _led[LED_FRAME_GREEN(index)] = dataG;
  _led[LED_FRAME_BLUE(index)] = dataB;
  _led[LED_FRAME_BRIGHTNESS(index)] = dataBrightness;
  _led[LED_FRAME_CURRENT(index)] = dataCurrent;
}

Arduino_APA102::~Arduino_APA102(){
  free(_led);
}

void Arduino_APA102::begin(void){
  pinMode(_SDA_pin, OUTPUT);
  pinMode(_SCK_pin, OUTPUT);

  digitalWrite(_SDA_pin, LOW);
  digitalWrite(_SCK_pin, LOW);

  clear(); // Default data, empty colors, full Current and Brightness
}

void Arduino_APA102::end(void){
  pinMode(_SDA_pin, INPUT);
  pinMode(_SCK_pin, INPUT);
}

void Arduino_APA102::show(void){
  // 3 blocks of 32 bits:
  // [0x00][0x00][0x00][0x00] - START LED, (startFrame)
  // [LED | Current][B][G][R] - LED data
  //  3bit|5bit      8b 8b 8b
  // [0xFF][0xFF][0xFF][0xFF] - START LED (endFrame) - not all 1s, Adafruit_DotStar found the way to avoid the empty LEDs become white

  _startFrame();

  // Get the data from the buffer
  // Send to the line
  // Each LED has 5 bytes

  for (int c = 0; c < _numLeds; c++){
    uint8_t bright = _led[LED_FRAME_BRIGHTNESS(c)];
  
    uint16_t newRed = map(bright, 0, 100, 0, _led[LED_FRAME_RED(c)]);
    uint16_t newGreen = map(bright, 0, 100, 0, _led[LED_FRAME_GREEN(c)]);
    uint16_t newBlue = map(bright, 0, 100, 0, _led[LED_FRAME_BLUE(c)]);

    uint8_t current = uint8_t(_led[LED_FRAME_CURRENT(c)]);

    _write8(uint8_t(0b111 << 5 | current));
    _write8(newBlue);
    _write8(newGreen);
    _write8(newRed);
  }

  _endFrame();
}

void Arduino_APA102::setPixelColor(uint16_t indexLed, uint32_t newColor){
  uint8_t newRed = uint8_t(newColor >> 16);
  uint8_t newGreen = uint8_t(newColor >> 8);
  uint8_t newBlue = uint8_t(newColor);

  setPixelColor(indexLed, newRed, newGreen, newBlue);
}

void Arduino_APA102::setPixelColor(uint16_t indexLed, uint8_t red, uint8_t green, uint8_t blue){
  if (indexLed < 0 && indexLed > _numLeds){
  }else{

    uint8_t brightness = _led[LED_FRAME_BRIGHTNESS(indexLed)];

    _led[LED_FRAME_RED(indexLed)] = red;
    _led[LED_FRAME_GREEN(indexLed)] = green;
    _led[LED_FRAME_BLUE(indexLed)] = blue;
  }
}

void Arduino_APA102::fill(uint32_t newColor, uint16_t startLed, uint16_t count){
  for (int c = startLed; c < count; c++){
    setPixelColor(c, newColor);
  }
}

// Set a global Brightness
void Arduino_APA102::setBrightness(uint8_t newBrightness){
  for (int i = 0; i < _numLeds; i++){
    setBrightness(i, newBrightness);
  }
}

// Set individual LED brightness
void Arduino_APA102::setBrightness(uint8_t indexLed, uint8_t newBrightness){
  _led[LED_FRAME_BRIGHTNESS(indexLed)] = newBrightness;
}

// Set global Max current, its NOT brightness, depending on the color its going to look different even if it has the same max current and amoumt of color (LEDs color's voltage)
void Arduino_APA102::setCurrent(uint8_t newCurrent){
  for (int i = 0; i < _numLeds; i++){
    setCurrent(i, newCurrent);
  }
}
// Set each LED's voltage
void Arduino_APA102::setCurrent(uint8_t indexLed, uint8_t newCurrent){
  _led[(indexLed * 5) + 4] = newCurrent;
}

// Empty all he LEDs
// Default data
void Arduino_APA102::clear(){
  memset(_led, 0, _numLeds);
  for (int c = 0; c < _numLeds; c++){
    _led[LED_FRAME_RED(c)] = 0;
    _led[LED_FRAME_GREEN(c)] = 0;
    _led[LED_FRAME_BLUE(c)] = 0;

    _led[LED_FRAME_BRIGHTNESS(c)] = 100; //Max bright 100%
    _led[LED_FRAME_CURRENT(c)] = 31;  //Max Current, 0b11111
  }
}

//Protocol blocks

// Start frame block
void Arduino_APA102::_startFrame(){
  for (int i = 0; i < 4; i++){
    _write8(0x00);
  }
}

// End frame block
void Arduino_APA102::_endFrame(){
  for (int i = 0; i < ((_numLeds + 15) / 16); i++){ //Avoid to set the left LEDs white, taken from Adafruit_DotStar
    _write8(0xFF); //
  }
}

// Send the data to the Line
void Arduino_APA102::_write8(uint8_t data){
  // Convert the bit into a state H/L
  for (uint8_t i = 8; i--; data <<= 1){

    if (data & 0x80){
      digitalWrite(_SDA_pin, HIGH);
    }else{
      digitalWrite(_SDA_pin, LOW);
    }

    // Pulse
    digitalWrite(_SCK_pin, HIGH);
    digitalWrite(_SCK_pin, LOW);
  }
}