// ==========================================
// UANIMA Neopixel Library - Brightness & Pixel Control Example
// ==========================================
// Demonstrates: setBrightness(), getBrightness(), setPixelColor(),
// getPixelColor(), fill(), setPin(), Wheel() and heatColor()

#include "DevLab_UANIMA.h"

// Configuration
#define PIN 6        // GPIO pin connected to Neopixels
#define NUMPIXELS 128 // Number of LEDs

DevLab_UANIMA unStrip(NUMPIXELS, PIN);

void setup() {
    Serial.begin(115200);

    // setPin() lets you (re)assign the data pin. Call it BEFORE begin() -
    // calling it afterwards makes Adafruit_NeoPixel re-run pinMode()/
    // digitalWrite() on that pin, which on platforms that route Neopixel
    // output through a peripheral (like the RMT peripheral on ESP32) can
    // silently detach the pin from that peripheral, "freezing" the strip
    // on whatever was last successfully shown.
    unStrip.setPin(PIN);

    // begin() sets an initial brightness (64 by default)
    unStrip.begin();

    // Change brightness independently, any time after begin()
    unStrip.setBrightness(30);
    Serial.print("Brightness set to: ");
    Serial.println(unStrip.getBrightness());

    // fill() paints every pixel in one call
    unStrip.fill(unStrip.Color(0, 0, 255)); // whole strip blue
    unStrip.show();
    delay(1000);

    // fill() also accepts a range: paint only the first 10 pixels
    unStrip.fill(unStrip.Color(0, 255, 0), 0, 10); // first 10 pixels green
    unStrip.show();
    delay(1000);

    // setPixelColor() controls a single pixel directly
    unStrip.setPixelColor(20, unStrip.Color(255, 0, 0));
    unStrip.show();

    // getPixelColor() reads back the color currently held by a pixel.
    // Note: this won't be an exact match of what you passed in - the
    // strip stores colors already scaled by the current brightness, and
    // getPixelColor() un-scales them back, which is lossy (rounding).
    uint32_t color = unStrip.getPixelColor(20);
    Serial.print("Pixel 20 color (packed RGB): 0x");
    Serial.println(color, HEX);
    delay(1000);

    // Wheel() and heatColor() are the low-level color helpers the built-in
    // effects use internally (rainbowCycle/confetti and fire, respectively)
    // - you can call them directly to build your own custom gradients.
    unStrip.clear();
    for (uint16_t i = 0; i < 10; i++) {
        unStrip.setPixelColor(30 + i, unStrip.Wheel(i * 25)); // rainbow gradient
        unStrip.setPixelColor(45 + i, unStrip.heatColor(i * 25)); // fire gradient
    }
    unStrip.show();
    delay(1000);
}

void loop() {
    // Fade the whole strip in and out using setBrightness() alone,
    // without touching the pixel colors set in setup().
    //
    // IMPORTANT: never let this reach 0. setBrightness() doesn't just
    // change how bright the strip LOOKS - it destructively rescales the
    // stored pixel data every time it's called. Adafruit_NeoPixel's
    // internal math has a hard edge case at brightness 0 (it's used as a
    // "no scaling yet" sentinel), and once you hit it, every future
    // setBrightness() call multiplies your colors by zero forever - the
    // strip goes black and *cannot* recover without redrawing the pixels
    // from scratch. Keeping a floor above 0 (5 here) avoids that trap.
    for (int b = 5; b <= 60; b += 5) {
        unStrip.setBrightness(b);
        unStrip.show();
        delay(50);
    }
    for (int b = 60; b >= 5; b -= 5) {
        unStrip.setBrightness(b);
        unStrip.show();
        delay(50);
    }
}
