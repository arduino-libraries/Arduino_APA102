#include "Arduino_APA102.h"

int dataPin = 5;
int clockPin = 4;
int totalLEDs = 5;

// Construct object, Arduino_APA102(nLEDS, data line, clock line)
Arduino_APA102 leds(totalLEDs, dataPin, clockPin);

//uint32_t color = random(0, 0xFFFFFF);                    // 0x[R][G][B]
uint32_t color_red = leds.Color( 255 , 0 , 0);  // Save yor color
uint32_t color_blue = leds.Color( 0 , 255 , 0);  // Save yor color
uint32_t color_green = leds.Color( 0 , 0 , 255);  // Save yor color


int r = 0;
int g = 100;
int b = 250;

void setup() {
  // put your setup code here, to run once:
  leds.begin();

  leds.setPixelColor(0 , color_red);
  leds.setPixelColor(1 , color_red);
  leds.setPixelColor(2 , color_green);
  leds.setPixelColor(3 , color_green);
  leds.setPixelColor(4 , color_blue);
  leds.show();

  delay(2500);  
  // Brigtness does not change the Max Current, you control the PWM duty cycle of the APA102
  // With the same Max current set in 2 LEDs, you can see different phyisical brightness
  // depending on the use of each or combination of the internal rgb LEDs which each APA102 component has
  // You can see the effect:
  //
  // Current can be set from 0-31
  // Brightness from 0% - 100%
  
  leds.setCurrent(0,5);
  leds.setCurrent(1,31);
  leds.setCurrent(2,0);
  leds.setCurrent(3,1);
  leds.setCurrent(4,20);
  leds.show();
}

void loop() {
  // put your main code here, to run repeatedly:

}