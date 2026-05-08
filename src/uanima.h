

#ifndef INC_UANIMA_H_
#define INC_UANIMA_H_

#include <Adafruit_NeoPixel.h>

#define PIN        8
#define NUMPIXELS 25


// animations.h
extern Adafruit_NeoPixel pixels;


void setupAnimSetting(Adafruit_NeoPixel& pixels);

void colorWipe(Adafruit_NeoPixel& pixels,uint32_t color, int wait);

void theaterChase(Adafruit_NeoPixel& pixels,uint32_t color, int wait);

void quetzalcoatlEffect(Adafruit_NeoPixel& pixels,int wait);

uint32_t Wheel(Adafruit_NeoPixel& pixels,byte WheelPos);

void rainbowCycle(Adafruit_NeoPixel& pixels,int wait);

void scanner(Adafruit_NeoPixel& pixels,uint32_t color, int wait);

void confetti(Adafruit_NeoPixel& pixels,int wait);

void fadeInOut(Adafruit_NeoPixel& pixels,uint32_t color);



#endif /* INC_ANIMATIONS_H_ */