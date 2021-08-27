# APA102 library

## Methods

### `Arduino_APA102(numLEDs, newDataPin , newClockPin)`

Attach the LEDs to the pins, and save the number of total LEDs.

#### Syntax

```
Arduino_APA102 leds(totalLEDs, dataPin, clockPin);
```

#### Parameters

* numLEDs : Amount of the LEDs to control
* dataPin : Pin connected to SDI (DATA)
* clockPin : Pîn connected to CKI (CLOCK)


#### Example

```
#include <Arduino_APA102.h> 

Arduino_APA102 leds(5, 5, 4);

void setup() {} 
void loop() {} 
```

#### See also

* [begin()](#attached)
* [setPixelColor()](#setPixelColor)
* [show()](#show)

### `begin()`

Initialize the pins to control the devices attached.

#### Syntax

```
leds.begin()
```

#### Example

```
#include <Arduino_APA102.h> 

Arduino_APA102 leds(5, 5, 4);

void setup() {
  leds.begin();
} 
void loop() {} 
```
#### See also

* [setPixelColor()](#setPixelColor)
* [show()](#show)
* [end()](#end)

### `end()`

Disable the lines

#### Syntax

```
leds.end()
```

#### See also

* [begin()](#setPixelColor)


### `setPixelColor()`

Saves the color value 

#### Syntax

````
leds.setPixelColor(indexLed, newColor)
````

#### Parameters

* indexLed: LED index number
* newColor: the value of the R G and B togetger i.e 0xFFFFFF(white) or 255,255,255 (int)

#### Example

```
#include <Arduino_APA102.h> 

Arduino_APA102 leds(5, 5, 4);

void setup() {
  leds.begin();
} 
void loop() {
  leds.setPixelColor(0, 0xFF00FF);
  leds.setPixelColor(1, 255, 0, 255);
  leds.setPixelColor(2, 0, 0, 255);
  leds.show();
} 
```

#### See also

* [fill()](#fill)
* [setBrightness()](#setBrightness)
* [show()](#show)


### `fill()`

Write the color to a consecutive chain of LEDs, i.e from 4th count 5 then LEDs 4 to 9 will be saved with the same color.

#### Syntax

````
leds.fill(newColor, startLed, count)
````

#### Parameters

* newColor: color value see[Color](#Color)
* startLed: Index to start counting
* count: Forwarding LEDs that are going to be set.

#### See also

* [setPixelColor()](#setPixelColor)
* [setBrightness()](#show)
* [show()](#show)

### `setBrightness()`

Set the brightness of the LEDs, this scales the values that have been set by [setPixelColor()](#setPixelColor) and scale them by the percentage used in the parameter.

#### Syntax

```
led.setBrightness(50)
```

#### Parameters

* (optional) IndexLed: Choose one LED to change its value
* newBrightness: Percentage amount to scale the color's values of the LEDs (0% - 100%)


#### Example

```
#include <Arduino_APA102.h> 

Arduino_APA102 leds(5, 5, 4);

void setup() {
  leds.begin();

  leds.setPixelColor(0, 0xFFFFFF);
  leds.setPixelColor(1, 0xFFFFFF);
  leds.show();
  delay(1000);
} 

void loop() {
  leds.setBrightness(50); //Set global brightness
  leds.show();
  delay(1000);

  leds.setBrightness(0, 10);  //Change LED 0 's brightness
  leds.show();
  delay(1000);
} 
```

#### See also

* [setPixelColor()](#setPixelColor)
* [setBrightness()](#show)
* [show()](#show)

### `setCurrent()`

Control the internal PWM duty cycle of the LEDs, remember that this is not the same as brightness, with the same duty cycle you can have different brightness depending on the colors used.

Value from 0(min) to 31(max)

#### Syntax

```
leds.setCurrent(31)   //Global
leds.setCurrent(0,31) //Individual
```

#### Parameters
* (optional)indexLed: LED to set
* newCurrent: PWM duty cycle, from 0 to 31

#### See also

* [setPixelColor()](#setPixelColor)
* [setBrightness()](#show)
* [show()](#show)
