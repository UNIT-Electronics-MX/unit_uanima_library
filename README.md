# UANIMA Neopixel Library

Arduino library for **Addressable RGB LEDs (Neopixels)**, created by **Jonathan Mejorado López** and **Cesar Bautista**.

A lightweight library for Neopixel effects and animations using the Adafruit_NeoPixel library.

## Installation

1. Download the library from GitHub
2. Place in your Arduino `libraries` folder
3. Restart the Arduino IDE
4. Include the library: `#include "uanima.h"`

## Configuration

Define your PIN and number of LEDs, then create the `unStrip` object:

```cpp
#include "uanima.h"

#define PIN 8           // GPIO pin connected to Neopixels
#define NUMPIXELS 25    // Number of LEDs in your strip

// Create the Neopixel strip object
Adafruit_NeoPixel unStrip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
```

### Neopixel Type

The library uses: `NEO_GRB + NEO_KHZ800` (GRB color order, 800 kHz frequency)

## Available Functions

- **setupAnimSetting()** - Initialize the Neopixel strip
- **colorWipe()** - Color wipe animation
- **theaterChase()** - Theater chase animation
- **quetzalcoatlEffect()** - Aztec-themed animation effect
- **rainbowCycle()** - Rainbow cycling animation
- **scanner()** - Scanning light effect
- **confetti()** - Confetti animation
- **fadeInOut()** - Fade in and out effect

## Example Usage

```cpp
#include "uanima.h"

#define PIN 8           // GPIO pin connected to Neopixels
#define NUMPIXELS 25    // Number of LEDs

// Create the Neopixel strip object
Adafruit_NeoPixel unStrip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50

void setup() {
    setupAnimSetting(unStrip);  // Initialize with brightness 64
}

void loop() {
    colorWipe(unStrip, unStrip.Color(255, 0, 0), DELAYVAL);  // Red wipe
    delay(500);
    
    unStrip.clear();
    unStrip.show();
    delay(1000);
}
```

## License

See [License.h](License.h) for license information.
