#include "DevLab_UANIMA.h"
#include <math.h>

DevLab_UANIMA::DevLab_UANIMA(uint16_t numPixels, int16_t pin, neoPixelType type)
    : strip(numPixels, pin, type) {
    heatBuffer = new uint8_t[strip.numPixels()];
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        heatBuffer[i] = 0;
    }
}

DevLab_UANIMA::~DevLab_UANIMA() {
    delete[] heatBuffer;
}

void DevLab_UANIMA::begin(uint8_t brightness) {
    strip.begin();
    strip.setBrightness(brightness);
    strip.clear();
    strip.show();
}

void DevLab_UANIMA::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
}

uint8_t DevLab_UANIMA::getBrightness() const {
    return strip.getBrightness();
}

void DevLab_UANIMA::setPin(int16_t pin) {
    strip.setPin(pin);
}

void DevLab_UANIMA::setPixelColor(uint16_t n, uint32_t color) {
    strip.setPixelColor(n, color);
}

uint32_t DevLab_UANIMA::getPixelColor(uint16_t n) const {
    return strip.getPixelColor(n);
}

void DevLab_UANIMA::fill(uint32_t color, uint16_t first, uint16_t count) {
    strip.fill(color, first, count);
}

void DevLab_UANIMA::setMatrixSize(uint16_t width, uint16_t height, MatrixLayout layout) {
    matW = width;
    matH = height;
    matLayout = layout;
}

uint16_t DevLab_UANIMA::matrixWidth() const {
    return matW;
}

uint16_t DevLab_UANIMA::matrixHeight() const {
    return matH;
}

uint16_t DevLab_UANIMA::xy(uint16_t x, uint16_t y) const {
    // (0, 0) is the top-left corner; x grows right, y grows down,
    // regardless of the physical wiring direction configured below.
    switch (matLayout) {
        case MATRIX_COLUMN_MAJOR_PROGRESSIVE: {
            uint16_t row = matH - 1 - y; // wiring starts at the bottom row
            return x * matH + row;
        }
        case MATRIX_COLUMN_MAJOR_SERPENTINE: {
            uint16_t row = matH - 1 - y;
            return (x % 2 == 0) ? (x * matH + row) : (x * matH + (matH - 1 - row));
        }
        case MATRIX_ROW_MAJOR_SERPENTINE:
            return (y % 2 == 0) ? (y * matW + x) : (y * matW + (matW - 1 - x));
        case MATRIX_ROW_MAJOR_PROGRESSIVE:
        default:
            return y * matW + x;
    }
}

void DevLab_UANIMA::setPixelColorXY(uint16_t x, uint16_t y, uint32_t color) {
    strip.setPixelColor(xy(x, y), color);
}

uint32_t DevLab_UANIMA::getPixelColorXY(uint16_t x, uint16_t y) const {
    return strip.getPixelColor(xy(x, y));
}

uint32_t DevLab_UANIMA::Color(uint8_t r, uint8_t g, uint8_t b) {
    return strip.Color(r, g, b);
}

uint16_t DevLab_UANIMA::numPixels() const {
    return strip.numPixels();
}

void DevLab_UANIMA::clear() {
    strip.clear();
}

void DevLab_UANIMA::show() {
    strip.show();
}

void DevLab_UANIMA::colorWipe(uint32_t color, int wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}

void DevLab_UANIMA::theaterChase(uint32_t color, int wait) {
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 3; b++) {
            strip.clear();
            for (uint16_t i = b; i < strip.numPixels(); i += 3) {
                strip.setPixelColor(i, color);
            }
            strip.show();
            delay(wait);
        }
    }
}


const int SNAKE_LEN = 7;

uint32_t aztecPalette[] = {
    0x228B22,
    0xDAA520,
    0xB22222,
    0xFFD700,
    0x006400
};

void DevLab_UANIMA::quetzalcoatlEffect(int wait) {
    int head = 0;
    int paletteSize = sizeof(aztecPalette) / sizeof(aztecPalette[0]);
    int totalPixels = strip.numPixels();

    for (int step = 0; step < totalPixels + SNAKE_LEN; step++) {
        strip.clear();

        for (int i = 0; i < SNAKE_LEN; i++) {
            int idx = (head - i + totalPixels) % totalPixels;
            uint32_t color = aztecPalette[i % paletteSize];
            strip.setPixelColor(idx, color);
        }

        strip.show();
        delay(wait);
        head = (head + 1) % totalPixels;
    }
}

uint32_t DevLab_UANIMA::Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

uint32_t DevLab_UANIMA::heatColor(uint8_t temperature) const {
    uint8_t t192 = (uint8_t)((temperature / 255.0) * 191);
    uint8_t heatramp = (t192 & 0x3F) << 2;

    if (t192 > 0x80) {
        return strip.Color(255, 255, heatramp);
    } else if (t192 > 0x40) {
        return strip.Color(255, heatramp, 0);
    } else {
        return strip.Color(heatramp, 0, 0);
    }
}

void DevLab_UANIMA::rainbowCycle(int wait) {
    for (int j = 0; j < 256; j++) {
        uint16_t totalPixels = strip.numPixels();
        for (uint16_t i = 0; i < totalPixels; i++) {
            strip.setPixelColor(i, Wheel((i * 256 / totalPixels + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}



void DevLab_UANIMA::scanner(uint32_t color, int wait) {
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        strip.clear();
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
    for (int i = (int)totalPixels - 2; i > 0; i--) {
        strip.clear();
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}

void DevLab_UANIMA::confettiStep(int wait) {
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        strip.setPixelColor(i, strip.Color(r * 0.94, g * 0.94, b * 0.94));
    }
    int pos = random(totalPixels);
    strip.setPixelColor(pos, Wheel(random(0, 255)));
    strip.show();
    delay(wait);
}

void DevLab_UANIMA::confetti(int wait) {
    unsigned long start = millis();
    while (millis() - start < 3000) {
        confettiStep(wait);
    }
}

void DevLab_UANIMA::fadeInOut(uint32_t color, int wait) {
    const int peak = 64;
    for (int step = 0; step <= peak * 2; step++) {
        int bri = (step <= peak) ? step : (peak * 2 - step);
        strip.fill(scaleColor(color, bri));
        strip.show();
        delay(wait);
    }
    strip.clear();
    strip.show();
}

uint32_t DevLab_UANIMA::scaleColor(uint32_t color, uint8_t bri) const {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    return strip.Color((uint8_t)((r * bri) / 255), (uint8_t)((g * bri) / 255), (uint8_t)((b * bri) / 255));
}

void DevLab_UANIMA::meteorFrame(uint32_t color, uint8_t size, uint8_t decay, int position) {
    uint16_t totalPixels = strip.numPixels();
    float keep = (100 - decay) / 100.0;

    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (uint8_t)(((c >> 16) & 0xFF) * keep);
        uint8_t g = (uint8_t)(((c >> 8) & 0xFF) * keep);
        uint8_t b = (uint8_t)((c & 0xFF) * keep);
        strip.setPixelColor(i, strip.Color(r, g, b));
    }

    for (int i = 0; i < size; i++) {
        int idx = position - i;
        if (idx >= 0 && idx < (int)totalPixels) {
            strip.setPixelColor(idx, color);
        }
    }
}

void DevLab_UANIMA::meteor(uint32_t color, int wait, uint8_t size, uint8_t decay) {
    strip.clear();
    int totalPixels = strip.numPixels();
    for (int position = 0; position < totalPixels + size; position++) {
        meteorFrame(color, size, decay, position);
        strip.show();
        delay(wait);
    }
}

void DevLab_UANIMA::twinkleStep(uint32_t color, int wait) {
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        strip.setPixelColor(i, strip.Color(r * 0.80, g * 0.80, b * 0.80));
    }
    if (random(100) < 40) {
        strip.setPixelColor(random(totalPixels), color);
    }
    strip.show();
    delay(wait);
}

void DevLab_UANIMA::twinkle(uint32_t color, int wait, unsigned long duration) {
    strip.clear();
    unsigned long start = millis();
    while (millis() - start < duration) {
        twinkleStep(color, wait);
    }
}

void DevLab_UANIMA::fireFrame(uint8_t cooling, uint8_t sparking) {
    uint16_t totalPixels = strip.numPixels();

    for (uint16_t i = 0; i < totalPixels; i++) {
        int cooldown = random(0, ((cooling * 10) / totalPixels) + 2);
        heatBuffer[i] = (cooldown >= heatBuffer[i]) ? 0 : heatBuffer[i] - cooldown;
    }

    if (totalPixels >= 3) {
        for (uint16_t k = totalPixels - 1; k >= 2; k--) {
            heatBuffer[k] = (heatBuffer[k - 1] + heatBuffer[k - 2] + heatBuffer[k - 2]) / 3;
        }
    }

    if (random(255) < sparking) {
        uint16_t sparkPixel = random(totalPixels < 7 ? totalPixels : 7);
        int newHeat = heatBuffer[sparkPixel] + random(160, 255);
        heatBuffer[sparkPixel] = (newHeat > 255) ? 255 : newHeat;
    }

    for (uint16_t j = 0; j < totalPixels; j++) {
        strip.setPixelColor(j, heatColor(heatBuffer[j]));
    }
}

void DevLab_UANIMA::fire(int wait, unsigned long duration, uint8_t cooling, uint8_t sparking) {
    unsigned long start = millis();
    while (millis() - start < duration) {
        fireFrame(cooling, sparking);
        strip.show();
        delay(wait);
    }
}

void DevLab_UANIMA::breathe(uint32_t color, int wait, uint8_t cycles, uint8_t maxBrightness) {
    const int stepsPerCycle = 100;
    for (int c = 0; c < cycles; c++) {
        for (int s = 0; s < stepsPerCycle; s++) {
            float phase = PI * s / stepsPerCycle;
            uint8_t bri = (uint8_t)(sin(phase) * maxBrightness);
            strip.fill(scaleColor(color, bri));
            strip.show();
            delay(wait);
        }
    }
    strip.clear();
    strip.show();
}

uint32_t DevLab_UANIMA::flagColorForPixel(uint16_t x, uint16_t y, uint16_t width, uint16_t height) const {
    uint16_t stripeWidth = width / 3;
    uint32_t stripeColor;
    if (x < stripeWidth) {
        stripeColor = strip.Color(0, 104, 71); // green (Pantone 3425 C approx.)
    } else if (x < (uint16_t)(width - stripeWidth)) {
        stripeColor = strip.Color(255, 255, 255); // white
    } else {
        stripeColor = strip.Color(206, 17, 38); // red (Pantone 1795 C approx.)
    }

    // Small dark emblem centered in the white stripe, standing in for the
    // coat of arms (eagle on a cactus devouring a snake) - too fine a
    // detail for this resolution, but without SOMETHING here it's
    // indistinguishable from the Italian flag. Uses the true geometric
    // center (not integer-divided) so it lands symmetrically regardless
    // of odd/even width or height.
    float cx = (width - 1) / 2.0;
    float cy = (height - 1) / 2.0;
    if (fabs((float)x - cx) <= 1.0 && fabs((float)y - cy) <= 1.0) {
        return strip.Color(60, 40, 20); // dark brown emblem mark
    }

    return stripeColor;
}

void DevLab_UANIMA::mexicanFlag(int wait, unsigned long waveDuration) {
    uint16_t width = matW > 0 ? matW : strip.numPixels();
    uint16_t height = matH > 0 ? matH : 1;

    // Raise the flag from the bottom row up.
    strip.clear();
    for (uint16_t step = 0; step < height; step++) {
        uint16_t y = height - 1 - step;
        for (uint16_t x = 0; x < width; x++) {
            uint32_t color = flagColorForPixel(x, y, width, height);
            if (matH > 0) {
                setPixelColorXY(x, y, color);
            } else {
                strip.setPixelColor(x, color);
            }
        }
        strip.show();
        delay(wait);
    }

    // Wave: each column bobs up/down (with a black sliver peeking in at the
    // edge it pulls away from) while also rippling in brightness, simulating
    // cloth moving in the air.
    unsigned long start = millis();
    float phase = 0;
    while (millis() - start < waveDuration) {
        for (uint16_t x = 0; x < width; x++) {
            float colPhase = phase + x * 0.6;
            int8_t rowOffset = (int8_t)round(sin(colPhase)); // -1, 0 or 1
            uint8_t waveBri = 150 + (uint8_t)(sin(colPhase) * 90);
            for (uint16_t y = 0; y < height; y++) {
                int16_t sourceY = (int16_t)y - rowOffset;
                uint32_t baseColor = (sourceY >= 0 && sourceY < (int16_t)height)
                    ? flagColorForPixel(x, (uint16_t)sourceY, width, height)
                    : 0; // black sliver where the fabric edge lifts away
                uint32_t shaded = scaleColor(baseColor, waveBri);
                if (matH > 0) {
                    setPixelColorXY(x, y, shaded);
                } else {
                    strip.setPixelColor(x, shaded);
                }
            }
        }
        strip.show();
        delay(wait);
        phase += 0.3;
    }
}

// ==========================================
// Non-blocking (millis-based) effect API
// ==========================================

void DevLab_UANIMA::startColorWipe(uint32_t color, uint16_t wait) {
    currentEffect = EFFECT_COLOR_WIPE;
    effectColor = color;
    stepWait = wait;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startTheaterChase(uint32_t color, uint16_t wait) {
    currentEffect = EFFECT_THEATER_CHASE;
    effectColor = color;
    stepWait = wait;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startQuetzalcoatlEffect(uint16_t wait) {
    currentEffect = EFFECT_QUETZALCOATL;
    stepWait = wait;
    stepIndex = 0;
    headPos = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startRainbowCycle(uint16_t wait) {
    currentEffect = EFFECT_RAINBOW_CYCLE;
    stepWait = wait;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startScanner(uint32_t color, uint16_t wait) {
    currentEffect = EFFECT_SCANNER;
    effectColor = color;
    stepWait = wait;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startConfetti(uint16_t wait, unsigned long duration) {
    currentEffect = EFFECT_CONFETTI;
    stepWait = wait;
    effectStartTime = millis();
    effectDuration = duration;
    lastStepTime = millis();
}

void DevLab_UANIMA::startFadeInOut(uint32_t color, uint16_t wait) {
    currentEffect = EFFECT_FADE_IN_OUT;
    effectColor = color;
    stepWait = wait;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startMeteor(uint32_t color, uint16_t wait, uint8_t size, uint8_t decay) {
    currentEffect = EFFECT_METEOR;
    effectColor = color;
    stepWait = wait;
    paramA = size;
    paramB = decay;
    stepIndex = 0;
    lastStepTime = millis();
    strip.clear();
}

void DevLab_UANIMA::startTwinkle(uint32_t color, uint16_t wait, unsigned long duration) {
    currentEffect = EFFECT_TWINKLE;
    effectColor = color;
    stepWait = wait;
    effectStartTime = millis();
    effectDuration = duration;
    lastStepTime = millis();
    strip.clear();
}

void DevLab_UANIMA::startFire(uint16_t wait, unsigned long duration, uint8_t cooling, uint8_t sparking) {
    currentEffect = EFFECT_FIRE;
    stepWait = wait;
    effectStartTime = millis();
    effectDuration = duration;
    paramA = cooling;
    paramB = sparking;
    lastStepTime = millis();
}

void DevLab_UANIMA::startBreathe(uint32_t color, uint16_t wait, uint8_t cycles, uint8_t maxBrightness) {
    currentEffect = EFFECT_BREATHE;
    effectColor = color;
    stepWait = wait;
    paramA = cycles;
    paramB = maxBrightness;
    stepIndex = 0;
    lastStepTime = millis();
}

void DevLab_UANIMA::startMexicanFlag(uint16_t wait, unsigned long waveDuration) {
    currentEffect = EFFECT_MEXICAN_FLAG;
    stepWait = wait;
    effectDuration = waveDuration;
    stepIndex = 0;
    wavePhase = 0;
    lastStepTime = millis();
    strip.clear();
}

void DevLab_UANIMA::stop() {
    currentEffect = EFFECT_NONE;
}

bool DevLab_UANIMA::isRunning() const {
    return currentEffect != EFFECT_NONE;
}

void DevLab_UANIMA::update() {
    if (currentEffect == EFFECT_NONE) {
        return;
    }

    unsigned long now = millis();
    if (now - lastStepTime < stepWait) {
        return;
    }
    lastStepTime = now;

    switch (currentEffect) {
        case EFFECT_COLOR_WIPE:    stepColorWipe();   break;
        case EFFECT_THEATER_CHASE: stepTheaterChase(); break;
        case EFFECT_QUETZALCOATL:  stepQuetzalcoatl(); break;
        case EFFECT_RAINBOW_CYCLE: stepRainbowCycle(); break;
        case EFFECT_SCANNER:       stepScanner();      break;
        case EFFECT_CONFETTI:      stepConfettiNB();   break;
        case EFFECT_FADE_IN_OUT:   stepFadeInOut();    break;
        case EFFECT_METEOR:        stepMeteor();       break;
        case EFFECT_TWINKLE:       stepTwinkleNB();     break;
        case EFFECT_FIRE:          stepFire();         break;
        case EFFECT_BREATHE:       stepBreathe();      break;
        case EFFECT_MEXICAN_FLAG:  stepMexicanFlag();  break;
        default: break;
    }
}

void DevLab_UANIMA::stepColorWipe() {
    if (stepIndex >= (int)strip.numPixels()) {
        currentEffect = EFFECT_NONE;
        return;
    }
    strip.setPixelColor(stepIndex, effectColor);
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepTheaterChase() {
    const int totalSteps = 30; // 10 repeats x 3 phases, matches theaterChase()
    if (stepIndex >= totalSteps) {
        currentEffect = EFFECT_NONE;
        return;
    }
    int b = stepIndex % 3;
    strip.clear();
    for (uint16_t i = b; i < strip.numPixels(); i += 3) {
        strip.setPixelColor(i, effectColor);
    }
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepQuetzalcoatl() {
    int totalPixels = strip.numPixels();
    if (stepIndex >= totalPixels + SNAKE_LEN) {
        currentEffect = EFFECT_NONE;
        return;
    }

    int paletteSize = sizeof(aztecPalette) / sizeof(aztecPalette[0]);
    strip.clear();
    for (int i = 0; i < SNAKE_LEN; i++) {
        int idx = (headPos - i + totalPixels) % totalPixels;
        strip.setPixelColor(idx, aztecPalette[i % paletteSize]);
    }
    strip.show();

    headPos = (headPos + 1) % totalPixels;
    stepIndex++;
}

void DevLab_UANIMA::stepRainbowCycle() {
    if (stepIndex >= 256) {
        currentEffect = EFFECT_NONE;
        return;
    }
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        strip.setPixelColor(i, Wheel((i * 256 / totalPixels + stepIndex) & 255));
    }
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepScanner() {
    int totalPixels = (int)strip.numPixels();
    int forwardSteps = totalPixels;
    int backwardSteps = totalPixels > 2 ? totalPixels - 2 : 0;
    int totalSteps = forwardSteps + backwardSteps;

    if (stepIndex >= totalSteps) {
        currentEffect = EFFECT_NONE;
        return;
    }

    int pixelIndex = (stepIndex < forwardSteps)
        ? stepIndex
        : totalPixels - 2 - (stepIndex - forwardSteps);

    strip.clear();
    strip.setPixelColor(pixelIndex, effectColor);
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepConfettiNB() {
    if (millis() - effectStartTime >= effectDuration) {
        currentEffect = EFFECT_NONE;
        return;
    }

    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        strip.setPixelColor(i, strip.Color(r * 0.94, g * 0.94, b * 0.94));
    }
    int pos = random(totalPixels);
    strip.setPixelColor(pos, Wheel(random(0, 255)));
    strip.show();
}

void DevLab_UANIMA::stepFadeInOut() {
    const int peak = 64;
    if (stepIndex > peak * 2) {
        currentEffect = EFFECT_NONE;
        return;
    }
    int bri = (stepIndex <= peak) ? stepIndex : (peak * 2 - stepIndex);
    strip.fill(scaleColor(effectColor, bri));
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepMeteor() {
    int totalPixels = strip.numPixels();
    if (stepIndex >= totalPixels + paramA) {
        currentEffect = EFFECT_NONE;
        return;
    }
    meteorFrame(effectColor, paramA, paramB, stepIndex);
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepTwinkleNB() {
    if (millis() - effectStartTime >= effectDuration) {
        currentEffect = EFFECT_NONE;
        return;
    }
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        strip.setPixelColor(i, strip.Color(r * 0.80, g * 0.80, b * 0.80));
    }
    if (random(100) < 40) {
        strip.setPixelColor(random(totalPixels), effectColor);
    }
    strip.show();
}

void DevLab_UANIMA::stepFire() {
    if (millis() - effectStartTime >= effectDuration) {
        currentEffect = EFFECT_NONE;
        return;
    }
    fireFrame(paramA, paramB);
    strip.show();
}

void DevLab_UANIMA::stepBreathe() {
    const int stepsPerCycle = 100;
    int totalSteps = (int)paramA * stepsPerCycle;
    if (stepIndex >= totalSteps) {
        strip.clear();
        strip.show();
        currentEffect = EFFECT_NONE;
        return;
    }
    int s = stepIndex % stepsPerCycle;
    float phase = PI * s / stepsPerCycle;
    uint8_t bri = (uint8_t)(sin(phase) * paramB);
    strip.fill(scaleColor(effectColor, bri));
    strip.show();
    stepIndex++;
}

void DevLab_UANIMA::stepMexicanFlag() {
    uint16_t width = matW > 0 ? matW : strip.numPixels();
    uint16_t height = matH > 0 ? matH : 1;

    if (stepIndex < height) {
        uint16_t y = height - 1 - stepIndex; // raise from the bottom row up
        for (uint16_t x = 0; x < width; x++) {
            uint32_t color = flagColorForPixel(x, y, width, height);
            if (matH > 0) {
                setPixelColorXY(x, y, color);
            } else {
                strip.setPixelColor(x, color);
            }
        }
        strip.show();
        stepIndex++;
        if (stepIndex == height) {
            effectStartTime = millis(); // start the wave timer once fully raised
        }
        return;
    }

    if (millis() - effectStartTime >= effectDuration) {
        currentEffect = EFFECT_NONE;
        return;
    }

    // Wave: each column bobs up/down (with a black sliver peeking in at the
    // edge it pulls away from) while also rippling in brightness, simulating
    // cloth moving in the air.
    for (uint16_t x = 0; x < width; x++) {
        float colPhase = wavePhase + x * 0.6;
        int8_t rowOffset = (int8_t)round(sin(colPhase)); // -1, 0 or 1
        uint8_t waveBri = 150 + (uint8_t)(sin(colPhase) * 90);
        for (uint16_t y = 0; y < height; y++) {
            int16_t sourceY = (int16_t)y - rowOffset;
            uint32_t baseColor = (sourceY >= 0 && sourceY < (int16_t)height)
                ? flagColorForPixel(x, (uint16_t)sourceY, width, height)
                : 0; // black sliver where the fabric edge lifts away
            uint32_t shaded = scaleColor(baseColor, waveBri);
            if (matH > 0) {
                setPixelColorXY(x, y, shaded);
            } else {
                strip.setPixelColor(x, shaded);
            }
        }
    }
    strip.show();
    wavePhase += 0.3;
}
