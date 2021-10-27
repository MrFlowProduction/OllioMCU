#include <Arduino.h>

#include <tools/leds.h>
#include <terminal.h>
#include <tools/expander.h>
#include <tools/scale.h>
#include <tools/adc.h>
#include <tools/lcd.h>
#include <businesslogic.h>
#include <tools/printer.h>
#include <tools/diag.h>





void setup() {
    INIT_TERMINAL();
    INIT_LCD();
    INIT_EXTERNAL_PORTS();
    INIT_LEDS();
    INIT_SCALE();
    INIT_ADC();
    INIT_PRINTER();
    INIT_MACHINE();

    syscheck();
}

void loop() {
  InitExpanderStates();
  terminal_handler();
  stateMachine();
}