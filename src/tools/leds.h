#ifndef LEDS_H /* include guards */
#define LEDS_H

#include <Arduino.h>    /* we need arduino functions to implement this */
#include <terminal.h>   /* Terminal */
#include <general/pinout.h>     /* Pinout */

/* handling LEDs */
void ledHandling();

/* Init ports */
void INIT_LEDS();

void led(bool);


#endif /* LEDS_H */