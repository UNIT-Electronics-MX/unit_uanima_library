/***************************************************************
 * @file    MatrixWiringTest.ino
 * @author  Jonathan Mejorado Lopez
 * @brief   Diagnostic sketch to figure out how a Neopixel matrix is
 *          wired internally, so setMatrixSize() can be configured
 *          correctly for animations that need real X/Y coordinates.
 *
 * Wiring (Neopixel matrix)
 * - Data -> 6
 * - VCC  -> 5V (or 3V3 if your matrix supports it)
 * - GND  -> GND
 ***************************************************************/

// Lights ONE pixel at a time, in index order (0, 1, 2...), slowly enough
// to watch. While this runs, watch the board and note:
//   1. Does the first row (pixels 0-7) light up left-to-right or
//      right-to-left?
//   2. When pixel #8 lights up, is it directly BELOW pixel #0, or directly
//      BELOW pixel #7? (This is the key question: "below #0" means
//      progressive/row-major wiring; "below #7" means serpentine/zigzag
//      wiring, which is the most common for pre-built matrix panels.)
//   3. Does this pattern repeat the same way for every row?

#include "DevLab_UANIMA.h"

#define PIN 6
#define NUMPIXELS 128

DevLab_UANIMA unStrip(NUMPIXELS, PIN);

int currentIndex = 0;
const unsigned long STEP_DELAY = 700; // ms between pixels - slow enough to watch

void setup() {
    Serial.begin(115200);
    unStrip.begin();

    // Once you've confirmed the wiring pattern with the raw index test
    // below, plug it in here and use (x, y) coordinates instead of raw
    // indices. This quick corner check lights each corner of the panel in
    // a different color - if setMatrixSize() matches your wiring, they
    // should land on the four physical corners.
    unStrip.setMatrixSize(16, 8, DevLab_UANIMA::MATRIX_COLUMN_MAJOR_PROGRESSIVE);
    Serial.print("Matrix size: ");
    Serial.print(unStrip.matrixWidth());
    Serial.print("x");
    Serial.println(unStrip.matrixHeight());

    uint16_t maxX = unStrip.matrixWidth() - 1;
    uint16_t maxY = unStrip.matrixHeight() - 1;
    unStrip.clear();
    unStrip.setPixelColorXY(0, 0, unStrip.Color(255, 0, 0));       // top-left: red
    unStrip.setPixelColorXY(maxX, 0, unStrip.Color(0, 255, 0));    // top-right: green
    unStrip.setPixelColorXY(0, maxY, unStrip.Color(0, 0, 255));    // bottom-left: blue
    unStrip.setPixelColorXY(maxX, maxY, unStrip.Color(255, 255, 0)); // bottom-right: yellow
    unStrip.show();

    Serial.print("xy(0, 0) maps to pixel index: ");
    Serial.println(unStrip.xy(0, 0));
    Serial.print("Color read back at (0, 0): 0x");
    Serial.println(unStrip.getPixelColorXY(0, 0), HEX);

    delay(3000);
    unStrip.clear();
    unStrip.show();
}

void loop() {
    unStrip.clear();
    unStrip.setPixelColor(currentIndex, unStrip.Color(255, 255, 255));
    unStrip.show();

    Serial.print("Pixel index: ");
    Serial.println(currentIndex);

    currentIndex = (currentIndex + 1) % unStrip.numPixels();
    delay(STEP_DELAY);
}
