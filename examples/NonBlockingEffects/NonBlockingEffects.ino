// ==========================================
// UANIMA Neopixel Library - Non-blocking Effects Example
// ==========================================
// Demonstrates the millis()-based start*()/update() API. Effects advance
// one frame at a time instead of blocking loop() with delay(), so the rest
// of your sketch keeps running. To prove it, a "heartbeat" message prints
// over Serial at a steady rate the whole time the strip is animating.
//
// NOTE: this example intentionally avoids driving any extra pin (like the
// board's built-in LED) to prove non-blocking behavior. On many ESP32
// boards LED_BUILTIN can be the same GPIO you're already using for the
// Neopixel data line (PIN below), and toggling it with pinMode()/
// digitalWrite() will silently break the Neopixel signal on that pin.

#include "DevLab_UANIMA.h"

// Configuration
#define PIN 6        // GPIO pin connected to Neopixels
#define NUMPIXELS 128 // Number of LEDs

DevLab_UANIMA unStrip(NUMPIXELS, PIN);

// Playlist of effects, run one after another
enum EffectStep {
    STEP_COLOR_WIPE,
    STEP_THEATER_CHASE,
    STEP_QUETZALCOATL,
    STEP_RAINBOW_CYCLE,
    STEP_SCANNER,
    STEP_CONFETTI,
    STEP_FADE_IN_OUT,
    STEP_METEOR,
    STEP_TWINKLE,
    STEP_FIRE,
    STEP_BREATHE,
    STEP_MEXICAN_FLAG,
    STEP_COUNT
};

int currentStep = STEP_COLOR_WIPE;
unsigned long effectStartedAt = 0;
const unsigned long MAX_EFFECT_TIME = 15000; // safety cap per effect, in ms

// Heartbeat state, runs independently of the strip animation
unsigned long lastHeartbeat = 0;
const unsigned long HEARTBEAT_INTERVAL = 1000;

void startCurrentEffect() {
    effectStartedAt = millis();
    switch (currentStep) {
        case STEP_COLOR_WIPE:
            unStrip.startColorWipe(unStrip.Color(255, 0, 0), 20);
            break;
        case STEP_THEATER_CHASE:
            unStrip.startTheaterChase(unStrip.Color(127, 127, 127), 40);
            break;
        case STEP_QUETZALCOATL:
            unStrip.startQuetzalcoatlEffect(60);
            break;
        case STEP_RAINBOW_CYCLE:
            unStrip.startRainbowCycle(10);
            break;
        case STEP_SCANNER:
            unStrip.startScanner(unStrip.Color(255, 0, 0), 20);
            break;
        case STEP_CONFETTI:
            unStrip.startConfetti(30, 3000); // run for 3 seconds
            break;
        case STEP_FADE_IN_OUT:
            unStrip.startFadeInOut(unStrip.Color(0, 0, 255), 10);
            break;
        case STEP_METEOR:
            unStrip.startMeteor(unStrip.Color(0, 128, 255), 20, 5, 30); // size 5, 30% trail decay
            break;
        case STEP_TWINKLE:
            unStrip.startTwinkle(unStrip.Color(255, 255, 255), 60, 3000); // 3 seconds
            break;
        case STEP_FIRE:
            unStrip.startFire(30, 4000, 55, 120); // 4 seconds, cooling 55, sparking 120
            break;
        case STEP_BREATHE:
            unStrip.startBreathe(unStrip.Color(128, 0, 255), 10, 3, 100); // 3 cycles, up to brightness 100
            break;
        case STEP_MEXICAN_FLAG:
            unStrip.startMexicanFlag(40, 3000); // 40ms per row, hold 3 seconds
            break;
    }
}

void setup() {
    Serial.begin(115200);
    unStrip.begin();
    unStrip.setMatrixSize(16, 8, DevLab_UANIMA::MATRIX_COLUMN_MAJOR_PROGRESSIVE);

    startCurrentEffect();
}

void loop() {
    // Advances the strip by one frame only if it's time for the next step.
    // It returns immediately otherwise - this call never blocks.
    unStrip.update();

    // Safety cutoff: forcibly stop() an effect if it somehow runs past its
    // expected duration (e.g. a much longer strip making quetzalcoatlEffect
    // take longer than planned).
    if (unStrip.isRunning() && millis() - effectStartedAt > MAX_EFFECT_TIME) {
        unStrip.stop();
    }

    // Once the current effect finishes, move on to the next one
    if (!unStrip.isRunning()) {
        currentStep = (currentStep + 1) % STEP_COUNT;
        unStrip.clear();
        unStrip.show();
        startCurrentEffect();
    }

    // Prints at a steady rate the whole time, proving loop() is never stuck
    // inside a delay() while the strip animates.
    unsigned long now = millis();
    if (now - lastHeartbeat >= HEARTBEAT_INTERVAL) {
        lastHeartbeat = now;
        Serial.println("still running...");
    }
}
