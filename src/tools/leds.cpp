#include "leds.h"

bool led_state = false;

void led(bool state){
    digitalWrite(LED, state);
    led_state = state;
}



void ledHandling(){
    led(!led_state);
}


void INIT_LEDS(){
    printinit("LEDS");
    pinMode(LED, OUTPUT);
    printdone();
}