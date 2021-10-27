#ifndef SYSTOOLS_H /* include guards */
#define SYSTOOLS_H

#include <Arduino.h>    /* we need arduino functions to implement this */
#include <terminal.h>   /* Terminal */
#include <Wire.h> 

void i2c_scanner();

byte i2c_address_check(byte);

/* ESP32 CHIP ID lekérdezése (MAC) */
uint32_t get_id();

/* Kiprinteli pár rendszer infót soros portra */
void print_sysinfo();

#endif