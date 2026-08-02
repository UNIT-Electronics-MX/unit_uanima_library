// ==========================================
// UANIMA Neopixel Library - Basic Example
// ==========================================

#include "DevLab_UANIMA.h"

// Configuration
#define PIN 6        // GPIO pin connected to Neopixels
#define NUMPIXELS 128         // Number of LEDs

// Create the animation object (configures the Neopixel strip internally)
DevLab_UANIMA unStrip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50  // Delay in milliseconds

void setup() {
    // Initialize the Neopixel strip
    // Brightness is set to 64 (0-255)
    unStrip.begin();
}

void loop() {
    // Red color sweep
    unStrip.colorWipe(unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);

    // Green color sweep
    unStrip.colorWipe(unStrip.Color(0, 255, 0), DELAYVAL);
    delay(500);

    // Blue color sweep
    unStrip.colorWipe(unStrip.Color(0, 0, 255), DELAYVAL);
    delay(500);

    // Clear all LEDs
    unStrip.clear();
    unStrip.show();
    delay(1000);
}
