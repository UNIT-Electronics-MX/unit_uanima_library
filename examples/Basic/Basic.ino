// ==========================================
// UANIMA Neopixel Library - Basic Example
// ==========================================

#include "uanima.h"

// Configuration
#define PIN 8        // GPIO pin connected to Neopixels
#define NUMPIXELS 25         // Number of LEDs

// Create the Neopixel strip object
Adafruit_NeoPixel unStrip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50  // Delay in milliseconds

void setup() {
    // Initialize the Neopixel strip
    // Brightness is set to 64 (0-255)
    setupAnimSetting(unStrip);
}

void loop() {
    // Red color sweep
    colorWipe(unStrip, unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);
    
    // Green color sweep
    colorWipe(unStrip, unStrip.Color(0, 255, 0), DELAYVAL);
    delay(500);
    
    // Blue color sweep
    colorWipe(unStrip, unStrip.Color(0, 0, 255), DELAYVAL);
    delay(500);
    
    // Clear all LEDs
    unStrip.clear();
    unStrip.show();
    delay(1000);
}
