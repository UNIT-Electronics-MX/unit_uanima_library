#include "uanima.h"


#define DELAYVAL   50
void setup() {
    setupAnimSetting(pixels);
}


void loop() {

    delay(500);
    //colorWipe(pixels, pixels.Color(255, 0, 0), DELAYVAL );
    //confetti(pixels,30);
    //theaterChase(pixels,pixels.Color(127,127,127),DELAYVAL);
    quetzalcoatlEffect(pixels,60);
    delay(500);
    
    pixels.clear();
    pixels.show();
    delay(1000);
}
