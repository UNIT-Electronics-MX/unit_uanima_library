# UANIMA Neopixel Library

Arduino library for **Addressable RGB LEDs (Neopixels)**, created by **Jonathan Mejorado López**.

A lightweight library for basic Neopixel effects and animations.

## UANIMA Class

### Initialization

* **setupAnimSetting(Adafruit_NeoPixel& pixels)** Init of main classes for working of pixels:
    - **begin()**
    - **setBrightness(uint8_t)**

```cpp
#include "uanima.h"


#define DELAYVAL   50

void setup() {
    setupAnimSetting(pixels);
}
```

### Public Methods

| Method | Description |
|--------|-------------|
| `void setupAnimSetting(Adafruit_NeoPixel& pixels)` | Initialize the main settings for init the neopixel leds |
| `void colorWipe(Adafruit_NeoPixel& pixels,uint32_t color, int wait)` | Display sequence of a specific colors per row |
| `void theaterChase(Adafruit_NeoPixel& pixels,uint32_t color, int wait)` | Display a cascade of light effects|
| `void quetzalcoatlEffect(Adafruit_NeoPixel& pixels,int wait);` | Display a effect of snake simulating quetzalcoatl|
| `uint32_t Wheel(Adafruit_NeoPixel& pixels,byte WheelPos);` | Display a effect of wheel|
| `void rainbowCycle(Adafruit_NeoPixel& pixels,int wait);` | Display a effect of rainbow in cycle|
| `void confetti(Adafruit_NeoPixel& pixels,int wait);` | Display a confetti effect |
| `void scanner(Adafruit_NeoPixel& pixels,uint32_t color, int wait);` | Display a scanner effect|
| `void fadeInOut(Adafruit_NeoPixel& pixels,uint32_t color);` | Display a simple fade effect|

## Color Format

Colors are defined in  a representation of 8 bits in decimal format per color: `0 - 255`

* Red: `0 - 255, 0, 0`
* Green: `0, 0 - 255, 0`
* Blue: `0, 0, 0 - 255`
* White: `255,255,255`

## License

See [License.h](License.h) for license information.
