/***************************************************************
 * @file    MexicanFlag.ino
 * @author  Jonathan Mejorado Lopez
 * @brief   Draws the Mexican flag on a 16x8 Neopixel matrix,
 *          "raising" it row by row from the bottom.
 *
 * Wiring (Neopixel matrix)
 * - Data -> 6
 * - VCC  -> 5V (or 3V3 if your matrix supports it)
 * - GND  -> GND
 ***************************************************************/

// This matrix is wired column-major, progressive: each column has 8
// pixels wired bottom->top, and column N+1 starts again at the bottom
// (not a serpentine/zigzag). If your matrix is wired differently, change
// the MatrixLayout argument in setMatrixSize() below - see DevLab_UANIMA.h
// for the available options.

#include "DevLab_UANIMA.h"

#define PIN 6
#define NUMPIXELS 128
#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 8

DevLab_UANIMA unStrip(NUMPIXELS, PIN);

void setup() {
    Serial.begin(115200);
    unStrip.begin();
    unStrip.setMatrixSize(MATRIX_WIDTH, MATRIX_HEIGHT, DevLab_UANIMA::MATRIX_COLUMN_MAJOR_PROGRESSIVE);
}

void loop() {
    // Blocking version: raises the flag (40ms per row) then holds it for
    // 5 seconds before repeating.
    unStrip.mexicanFlag(40, 5000);

    unStrip.clear();
    unStrip.show();
    delay(1000);
}
