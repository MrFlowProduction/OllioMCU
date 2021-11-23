#ifndef PRINTER_H /* include guards */
#define PRINTER_H

#include <Arduino.h>    /* we need arduino functions to implement this */
#include <terminal.h>
#include <general/pinout.h>
#include <general/globals.h>
#include <Adafruit_Thermal.h>
#include <tools/mem.h>
#include <tools/systools.h>
#include <tools/rtc.h>

/* Inicializálás */
void INIT_PRINTER();

/* Nyomtatás tesztelése */
void print_test();

/* parancs küldése a nyomtatónak */
void send_printer_cmd(const byte[], byte);

/* Van-e papír a nyomtatóban */
bool printerHasPaper();

/* Elismerő blokk nyomtatása */
void printBlock();


#endif /* PRINTER_H */