// ==========================================
// UANIMA Neopixel Library - All Effects Example
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
    // 1. Color Wipe - Red
    Serial.println("Running: Color Wipe (Red)");
    colorWipe(unStrip, unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);
    
    // 2. Theater Chase - White
    Serial.println("Running: Theater Chase (White)");
    theaterChase(unStrip, unStrip.Color(127, 127, 127), DELAYVAL);
    delay(500);
    
    // 3. Quetzalcoatl Effect - Aztec Animation
    Serial.println("Running: Quetzalcoatl Effect");
    quetzalcoatlEffect(unStrip, 60);
    delay(500);
    
    // 4. Rainbow Cycle
    Serial.println("Running: Rainbow Cycle");
    rainbowCycle(unStrip, 15);
    delay(500);
    
    // 5. Scanner - Red
    Serial.println("Running: Scanner (Red)");
    scanner(unStrip, unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);
    
    // 6. Confetti
    Serial.println("Running: Confetti");
    confetti(unStrip, 30);
    delay(500);
    
    // Clear all LEDs
    unStrip.clear();
    unStrip.show();
    delay(2000);
}
