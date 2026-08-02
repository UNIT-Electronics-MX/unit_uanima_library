
#ifndef DevLab_UANIMA_H
#define DevLab_UANIMA_H

#include <Adafruit_NeoPixel.h>

class DevLab_UANIMA {
    public:
        DevLab_UANIMA(uint16_t numPixels = 128, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800);

        ~DevLab_UANIMA();

        void begin(uint8_t brightness = 64);

        void setBrightness(uint8_t brightness);

        uint8_t getBrightness() const;

        void setPin(int16_t pin);

        void setPixelColor(uint16_t n, uint32_t color);

        uint32_t getPixelColor(uint16_t n) const;

        void fill(uint32_t color = 0, uint16_t first = 0, uint16_t count = 0);

        void colorWipe(uint32_t color, int wait);

        void theaterChase(uint32_t color, int wait);

        void quetzalcoatlEffect(int wait);

        uint32_t Wheel(byte WheelPos);

        uint32_t heatColor(uint8_t temperature) const;

        void rainbowCycle(int wait);

        void scanner(uint32_t color, int wait);

        void confetti(int wait);

        void fadeInOut(uint32_t color, int wait = 10);

        void meteor(uint32_t color, int wait, uint8_t size = 5, uint8_t decay = 30);

        void twinkle(uint32_t color, int wait, unsigned long duration = 3000);

        void fire(int wait, unsigned long duration = 3000, uint8_t cooling = 55, uint8_t sparking = 120);

        void breathe(uint32_t color, int wait, uint8_t cycles = 3, uint8_t maxBrightness = 100);

        uint32_t Color(uint8_t r, uint8_t g, uint8_t b);

        uint16_t numPixels() const;

        void clear();

        void show();

        // Matrix (2D) support. Configure once with setMatrixSize() so
        // xy()/setPixelColorXY()/getPixelColorXY() and effects like
        // mexicanFlag() know how to translate (x, y) into a linear pixel
        // index for your specific wiring. (0, 0) is the top-left corner;
        // x grows right, y grows down - regardless of the physical wiring
        // direction.
        enum MatrixLayout {
            MATRIX_ROW_MAJOR_PROGRESSIVE,    // every row wired left->right
            MATRIX_ROW_MAJOR_SERPENTINE,     // rows alternate direction (zigzag)
            MATRIX_COLUMN_MAJOR_PROGRESSIVE, // every column wired bottom->top
            MATRIX_COLUMN_MAJOR_SERPENTINE   // columns alternate direction (zigzag)
        };

        void setMatrixSize(uint16_t width, uint16_t height, MatrixLayout layout = MATRIX_ROW_MAJOR_PROGRESSIVE);

        uint16_t matrixWidth() const;

        uint16_t matrixHeight() const;

        uint16_t xy(uint16_t x, uint16_t y) const;

        void setPixelColorXY(uint16_t x, uint16_t y, uint32_t color);

        uint32_t getPixelColorXY(uint16_t x, uint16_t y) const;

        // Raises the flag row by row, then a brightness wave keeps sweeping
        // across the columns (simulating cloth moving in the wind) for
        // waveDuration ms.
        void mexicanFlag(int wait, unsigned long waveDuration = 5000);

        // Non-blocking (millis-based) effect API.
        // Call one start*() to launch an effect, then call update() on every
        // loop() iteration; it returns immediately unless it's time for the
        // next frame, so it never blocks with delay().
        void startColorWipe(uint32_t color, uint16_t wait);

        void startTheaterChase(uint32_t color, uint16_t wait);

        void startQuetzalcoatlEffect(uint16_t wait);

        void startRainbowCycle(uint16_t wait);

        void startScanner(uint32_t color, uint16_t wait);

        void startConfetti(uint16_t wait, unsigned long duration = 3000);

        void startFadeInOut(uint32_t color, uint16_t wait);

        void startMeteor(uint32_t color, uint16_t wait, uint8_t size = 5, uint8_t decay = 30);

        void startTwinkle(uint32_t color, uint16_t wait, unsigned long duration = 3000);

        void startFire(uint16_t wait, unsigned long duration = 3000, uint8_t cooling = 55, uint8_t sparking = 120);

        void startBreathe(uint32_t color, uint16_t wait, uint8_t cycles = 3, uint8_t maxBrightness = 100);

        void startMexicanFlag(uint16_t wait, unsigned long waveDuration = 5000);

        void update();

        void stop();

        bool isRunning() const;

    private:
        Adafruit_NeoPixel strip;

        void confettiStep(int wait);

        enum Effect {
            EFFECT_NONE,
            EFFECT_COLOR_WIPE,
            EFFECT_THEATER_CHASE,
            EFFECT_QUETZALCOATL,
            EFFECT_RAINBOW_CYCLE,
            EFFECT_SCANNER,
            EFFECT_CONFETTI,
            EFFECT_FADE_IN_OUT,
            EFFECT_METEOR,
            EFFECT_TWINKLE,
            EFFECT_FIRE,
            EFFECT_BREATHE,
            EFFECT_MEXICAN_FLAG
        };

        Effect currentEffect = EFFECT_NONE;
        unsigned long lastStepTime = 0;
        unsigned long effectStartTime = 0;
        unsigned long effectDuration = 0;
        uint16_t stepWait = 0;
        uint32_t effectColor = 0;
        int stepIndex = 0;
        int headPos = 0;
        uint8_t paramA = 0; // meteor size / fire cooling / breathe cycles
        uint8_t paramB = 0; // meteor decay / fire sparking / breathe max brightness

        uint8_t *heatBuffer;

        uint16_t matW = 0;
        uint16_t matH = 0;
        MatrixLayout matLayout = MATRIX_ROW_MAJOR_PROGRESSIVE;
        float wavePhase = 0;

        void stepColorWipe();
        void stepTheaterChase();
        void stepQuetzalcoatl();
        void stepRainbowCycle();
        void stepScanner();
        void stepConfettiNB();
        void stepFadeInOut();
        void stepMeteor();
        void stepTwinkleNB();
        void stepFire();
        void stepBreathe();
        void stepMexicanFlag();

        void meteorFrame(uint32_t color, uint8_t size, uint8_t decay, int position);
        void twinkleStep(uint32_t color, int wait);
        void fireFrame(uint8_t cooling, uint8_t sparking);
        uint32_t scaleColor(uint32_t color, uint8_t bri) const;
        uint32_t flagColorForPixel(uint16_t x, uint16_t y, uint16_t width, uint16_t height) const;
};

#endif /* DevLab_UANIMA_H_ */
