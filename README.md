# DevLab_UANIMA

Arduino library for **Addressable RGB LEDs (Neopixels)**, created by **Jonathan Mejorado Lopez** and **Cesar Bautista**.

A library of ready-made effects and animations for Neopixel strips and matrices, built on top of [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel). Every effect is available both as a simple blocking call and as a `millis()`-based non-blocking call, and there's built-in support for 2D matrices (any wiring pattern) and pixel-level access for building your own custom effects.

## Installation

1. Download this library
2. Place both in your Arduino `libraries` folder
3. Restart the Arduino IDE
4. Include the library: `#include "DevLab_UANIMA.h"`

## Quick start

```cpp
#include "DevLab_UANIMA.h"

#define PIN 6         // GPIO pin connected to the Neopixels
#define NUMPIXELS 128 // Number of LEDs in your strip

DevLab_UANIMA unStrip(NUMPIXELS, PIN); // NEO_GRB + NEO_KHZ800 by default

void setup() {
    unStrip.begin(); // brightness 64 by default
}

void loop() {
    unStrip.colorWipe(unStrip.Color(255, 0, 0), 50); // red wipe
    delay(500);

    unStrip.clear();
    unStrip.show();
    delay(1000);
}
```

See [examples/](examples/) for complete, runnable sketches - `Basic`, `AllEffects`, `NonBlockingEffects`, `BrightnessAndPixelControl`, `MatrixWiringTest` and `MexicanFlag`.

## Effects

Each effect below has a blocking version (runs to completion, uses `delay()`) and a non-blocking version prefixed with `start` (advances one frame per call to `update()`, never blocks). Both produce the same animation.

| Blocking | Non-blocking | Description |
|---|---|---|
| `colorWipe(color, wait)` | `startColorWipe(color, wait)` | Fills the strip one pixel at a time |
| `theaterChase(color, wait)` | `startTheaterChase(color, wait)` | Classic marquee chase |
| `quetzalcoatlEffect(wait)` | `startQuetzalcoatlEffect(wait)` | Aztec-themed color snake |
| `rainbowCycle(wait)` | `startRainbowCycle(wait)` | Rainbow cycling across the strip |
| `scanner(color, wait)` | `startScanner(color, wait)` | Knight Rider-style back-and-forth scanner |
| `confetti(wait)` | `startConfetti(wait, duration=3000)` | Random sparkling colors with fading trails |
| `fadeInOut(color, wait=10)` | `startFadeInOut(color, wait)` | Fades the whole strip in, then out |
| `meteor(color, wait, size=5, decay=30)` | `startMeteor(color, wait, size=5, decay=30)` | A bright head with a fading tail |
| `twinkle(color, wait, duration=3000)` | `startTwinkle(color, wait, duration=3000)` | Random sparkles on a fading background |
| `fire(wait, duration=3000, cooling=55, sparking=120)` | `startFire(wait, duration=3000, cooling=55, sparking=120)` | Simulated flicker (Fire2012-style) |
| `breathe(color, wait, cycles=3, maxBrightness=100)` | `startBreathe(color, wait, cycles=3, maxBrightness=100)` | Smooth sine-wave brightness pulse |
| `mexicanFlag(wait, waveDuration=5000)` | `startMexicanFlag(wait, waveDuration=5000)` | Raises the Mexican flag, then a wind-wave ripple (needs `setMatrixSize()` for the best look) |

To use the non-blocking API: call one `start*()` to launch an effect, then call `unStrip.update()` on every `loop()` iteration. Use `unStrip.isRunning()` to detect when it's done and `unStrip.stop()` to cancel it early.

```cpp
unStrip.startMeteor(unStrip.Color(0, 128, 255), 20);

void loop() {
    unStrip.update();      // never blocks
    if (!unStrip.isRunning()) {
        // effect finished - start the next one, or whatever else
    }
}
```

## Pixel & brightness control

- `setBrightness(brightness)` / `getBrightness()` - change brightness any time (not just at `begin()`)
- `setPixelColor(n, color)` / `getPixelColor(n)` - control a single pixel by index
- `fill(color, first=0, count=0)` - fill a range of pixels (or the whole strip)
- `setPin(pin)` - reassign the data pin at runtime (call **before** `begin()` - see note below)
- `Color(r, g, b)` - pack RGB into the 32-bit format the rest of the API expects
- `Wheel(pos)` / `heatColor(temperature)` - the color-gradient helpers used internally by `rainbowCycle`/`confetti` and `fire`, exposed so you can build your own gradients
- `numPixels()`, `clear()`, `show()`

## Matrix (2D) support

If your Neopixels are wired as a matrix rather than a single strip, configure it once and address pixels by `(x, y)` instead of a raw index:

```cpp
unStrip.setMatrixSize(16, 8, DevLab_UANIMA::MATRIX_COLUMN_MAJOR_PROGRESSIVE);
unStrip.setPixelColorXY(0, 0, unStrip.Color(255, 0, 0)); // top-left corner
```

`(0, 0)` is always the top-left corner and `y` grows downward, regardless of how the panel is actually wired. `MatrixLayout` covers the common wiring patterns:

- `MATRIX_ROW_MAJOR_PROGRESSIVE` - every row wired left→right, starting top-left
- `MATRIX_ROW_MAJOR_SERPENTINE` - rows alternate direction (zigzag), starting top-left
- `MATRIX_COLUMN_MAJOR_PROGRESSIVE` - every column wired bottom→top, starting bottom-left
- `MATRIX_COLUMN_MAJOR_SERPENTINE` - columns alternate direction (zigzag), starting bottom-left

Not sure how yours is wired? Run `examples/MatrixWiringTest` - it lights one pixel at a time so you can watch the physical pattern and figure out which layout matches.

Related: `matrixWidth()`, `matrixHeight()`, `xy(x, y)` (the raw index a coordinate maps to), `setPixelColorXY(x, y, color)`, `getPixelColorXY(x, y)`.

## Notes / gotchas

- **`setPin()`**: call it *before* `begin()`. Calling it afterward makes Adafruit_NeoPixel re-run `pinMode()`/`digitalWrite()` on that pin, which on platforms that route Neopixel output through a peripheral (e.g. the RMT peripheral on ESP32) can silently detach the pin from it.
- **`setBrightness(0)`**: avoid it in code that calls `setBrightness()` repeatedly (e.g. a manual breathing loop). Adafruit_NeoPixel's brightness scaling is destructive (it rescales the stored pixel buffer, not just the output), and hitting exactly 0 hits an internal divide-by-zero guard that zeroes your colors *permanently* - no later `setBrightness()` call can bring them back, only redrawing the pixels can. `breathe()`/`fadeInOut()` in this library avoid the issue entirely by scaling colors directly instead of touching the strip's brightness.
- **`LED_BUILTIN` on ESP32**: on some boards it's the same GPIO as a Neopixel data pin you might already be using. Don't `pinMode()`/`digitalWrite()` that pin elsewhere in your sketch if so - it'll break the Neopixel signal.

## License

See [LICENSE](LICENSE) for license information.
