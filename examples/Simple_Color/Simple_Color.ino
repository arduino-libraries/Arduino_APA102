#include "Arduino_APA102.h"

int dataPin = 5;
int clockPin = 4;
int totalLEDs = 5;

// Construct object, Arduino_APA102(nLEDS, data line, clock line)
Arduino_APA102 leds(totalLEDs, dataPin, clockPin);

//uint32_t color = random(0, 0xFFFFFF);                    // 0x[R][G][B]
uint32_t color_red = leds.Color( 255 , 0 , 0);  // Save yor color

int r = 0;
int g = 100;
int b = 250;

void setup() {
  // put your setup code here, to run once:
  leds.begin();

  leds.setPixelColor(0 , color_red);
  leds.setPixelColor(1 , r , g , b);
  leds.show();
}

void loop() {
  // put your main code here, to run repeatedly:

}