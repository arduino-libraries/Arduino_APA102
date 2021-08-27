#include "Arduino_APA102.h"

int dataPin = 5;
int clockPin = 4;
int totalLEDs = 5;

// Construct object, Arduino_APA102(nLEDS, data line, clock line)
Arduino_APA102 leds(totalLEDs, dataPin, clockPin);

uint32_t color = random(0, 0xFFFFFF);                    // 0x[R][G][B]
//uint32_t color_white = leds.Color( 255 , 255 , 255);  // Save yor color

void setup() {
  // put your setup code here, to run once:
  leds.begin();

  leds.fill(color, 0, totalLEDs);
  leds.show();
}

void loop() {
  // put your main code here, to run repeatedly:

  int brightness = 0;

  // ALL FADE
  // FADE IN
  for (brightness = 0; brightness < 101; brightness++ ) {
    leds.setBrightness(brightness);
    leds.show();
    delay(10);
  }
  // FADE OUT
  for (brightness = 100; brightness > -1; brightness-- ) {
    leds.setBrightness(brightness);
    leds.show();
    delay(10);
  }

  //Change color
  color = random(0, 0xFFFFFF);
  leds.fill(color, 0, totalLEDs);

  // INDIVIDUAL FADE
  for (int i = 0; i < totalLEDs; i++) {
    // FADE IN
    for (int brightness = 0; brightness < 101; brightness++) {
      leds.setBrightness(i , brightness);
      leds.show();
    }
  }

  // INDIVIDUAL FADE
  for (int i = 0; i < totalLEDs; i++) {
    // FADE OUT
    for (int brightness = 100; brightness > -1; brightness--) {
      leds.setBrightness(i , brightness);
      leds.show();
    }
  }
}