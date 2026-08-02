// ==========================================
// UANIMA Neopixel Library - All Effects Example
// ==========================================

#include "DevLab_UANIMA.h"

// Configuration
#define PIN 6        // GPIO pin connected to Neopixels
#define NUMPIXELS 128         // Number of LEDs

// Create the animation object (configures the Neopixel strip internally)
DevLab_UANIMA unStrip(128,6);

#define DELAYVAL 50  // Delay in milliseconds

void setup() {
    Serial.begin(115200);

    // Initialize the Neopixel strip
    // Brightness is set to 64 (0-255)
    unStrip.begin();
    unStrip.setMatrixSize(16, 8, DevLab_UANIMA::MATRIX_COLUMN_MAJOR_PROGRESSIVE);
}

void loop() {
    // 1. Color Wipe - Red
    Serial.println("Running: Color Wipe (Red)");
    unStrip.colorWipe(unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);

    // 2. Theater Chase - White
    Serial.println("Running: Theater Chase (White)");
    unStrip.theaterChase(unStrip.Color(127, 127, 127), DELAYVAL);
    delay(500);

    // 3. Quetzalcoatl Effect - Aztec Animation
    Serial.println("Running: Quetzalcoatl Effect");
    unStrip.quetzalcoatlEffect(60);
    delay(500);

    // 4. Rainbow Cycle
    Serial.println("Running: Rainbow Cycle");
    unStrip.rainbowCycle(15);
    delay(500);

    // 5. Scanner - Red
    Serial.println("Running: Scanner (Red)");
    unStrip.scanner(unStrip.Color(255, 0, 0), DELAYVAL);
    delay(500);

    // 6. Confetti
    Serial.println("Running: Confetti");
    unStrip.confetti(30);
    delay(500);

    // 7. Fade In/Out - Orange (blocking version)
    Serial.println("Running: Fade In/Out (Orange, blocking)");
    unStrip.fadeInOut(unStrip.Color(255, 128, 0), 10);
    delay(500);

    // 8. Meteor - Blue, shown both ways: first the blocking call, then the
    // non-blocking start*() + update() version.
    Serial.println("Running: Meteor (Blue, blocking)");
    unStrip.meteor(unStrip.Color(0, 128, 255), 20, 5, 30);
    delay(500);

    Serial.println("Running: Meteor (Blue, non-blocking)");
    unStrip.startMeteor(unStrip.Color(0, 128, 255), 20, 5, 30);
    while (unStrip.isRunning()) {
        unStrip.update();
    }
    delay(500);

    // 9. Twinkle - White, blocking then non-blocking.
    Serial.println("Running: Twinkle (White, blocking)");
    unStrip.twinkle(unStrip.Color(255, 255, 255), 60, 3000);
    delay(500);

    Serial.println("Running: Twinkle (White, non-blocking)");
    unStrip.startTwinkle(unStrip.Color(255, 255, 255), 60, 3000);
    while (unStrip.isRunning()) {
        unStrip.update();
    }
    delay(500);

    // 10. Fire, blocking then non-blocking.
    Serial.println("Running: Fire (blocking)");
    unStrip.fire(30, 4000, 55, 120);
    delay(500);

    Serial.println("Running: Fire (non-blocking)");
    unStrip.startFire(30, 4000, 55, 120);
    while (unStrip.isRunning()) {
        unStrip.update();
    }
    delay(500);

    // 11. Breathe - Purple, blocking then non-blocking.
    Serial.println("Running: Breathe (Purple, blocking)");
    unStrip.breathe(unStrip.Color(128, 0, 255), 10, 3, 100);
    delay(500);

    Serial.println("Running: Breathe (Purple, non-blocking)");
    unStrip.startBreathe(unStrip.Color(128, 0, 255), 10, 3, 100);
    while (unStrip.isRunning()) {
        unStrip.update();
    }
    delay(500);

    // 12. Mexican Flag (uses the 16x8 matrix configured in setup())
    Serial.println("Running: Mexican Flag");
    unStrip.mexicanFlag(40, 3000);
    delay(500);

    // Clear all LEDs
    unStrip.clear();
    unStrip.show();
    delay(2000);
}
