#include "uanima.h"

void setupAnimSetting(Adafruit_NeoPixel& strip){
    strip.begin();
    strip.setBrightness(64);
    strip.clear();
    strip.show();
}

void colorWipe(Adafruit_NeoPixel& strip,uint32_t color, int wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}

void theaterChase(Adafruit_NeoPixel& strip,uint32_t color, int wait) {
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

void quetzalcoatlEffect(Adafruit_NeoPixel& strip,int wait) {
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

uint32_t Wheel(Adafruit_NeoPixel& strip,byte WheelPos) {
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

void rainbowCycle(Adafruit_NeoPixel& strip,int wait) {
    for (int j = 0; j < 256; j++) {
        uint16_t totalPixels = strip.numPixels();
        for (uint16_t i = 0; i < totalPixels; i++) {
            strip.setPixelColor(i, Wheel(strip,(i * 256 / totalPixels + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}



void scanner(Adafruit_NeoPixel& strip,uint32_t color, int wait) {
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

void confettiSetup(Adafruit_NeoPixel& strip,int wait) {
    uint16_t totalPixels = strip.numPixels();
    for (uint16_t i = 0; i < totalPixels; i++) {
        uint32_t c = strip.getPixelColor(i);
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        strip.setPixelColor(i, strip.Color(r * 0.94, g * 0.94, b * 0.94));
    }
    int pos = random(totalPixels);
    strip.setPixelColor(pos, Wheel(strip,random(0, 255)));
    strip.show();
    delay(wait);
}

void confetti(Adafruit_NeoPixel& strip,int wait) {
    unsigned long start = millis();
    while (millis() - start < 3000) {
        confettiSetup(strip,wait);
    }
    
}
void fadeInOut(Adafruit_NeoPixel& strip,uint32_t color) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    for (int bri = 0; bri <= 64; bri++) {
        strip.setBrightness(bri);
        colorWipe(strip,strip.Color(r, g, b), 5);
    }
    for (int bri = 64; bri >= 0; bri--) {
        strip.setBrightness(bri);
        colorWipe(strip,strip.Color(r, g, b), 5);
    }
}

