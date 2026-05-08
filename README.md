# UANIMA Neopixel Library

Arduino library for **Addressable RGB LEDs (Neopixels)**, created by **Jonathan Mejorado López**.

A lightweight library for basic Neopixel effects and animations.

## UANIMA Class

### Initialization

* **void begin(uint8_t pin, uint16_t count)** Initializes the Neopixel strip on the specified pin with the given LED count.
* **void begin(uint8_t pin, uint16_t count, uint8_t brightness)** Initializes with custom brightness (0-255).

```cpp
#include "UANIMA.h"

UANIMA strip(6, 30);  // pin 6, 30 LEDs

void setup() {
    strip.begin();
    strip.setBrightness(255);
}

void loop() {
    strip.fill(0xFF0000);  // Red color
    strip.show();
    delay(500);
}
```

### Public Methods

| Method | Description |
|--------|-------------|
| `void begin()` | Initializes the LED strip |
| `void show()` | Display the current LED data |
| `void fill(uint32_t color)` | Fill all LEDs with a single color |
| `void setPixel(uint16_t index, uint32_t color)` | Set a single LED color |
| `void setBrightness(uint8_t level)` | Set brightness (0-255) |
| `void clear()` | Turn off all LEDs |

## Color Format

Colors are defined in hex format: `0xRRGGBB`

* Red: `0xFF0000`
* Green: `0x00FF00`
* Blue: `0x0000FF`
* White: `0xFFFFFF`

## License

See [License.h](License.h) for license information.
