#ifndef SCALE_H /* include guards */
#define SCALE_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <Wire.h>
#include <HX711.h>
#include <terminal.h>
#include <general/pinout.h>
#include <general/globals.h>
#include <tools/diag.h>

extern HX711 scale;

/* Init scale */
void INIT_SCALE();

/* Kalibráció */
void calibrateScale();

/* Acquire reading */
float read_scale();

/* Referencia pont beállítása */
void scaleZeroPoint();

/* Mérleg adatok kiprintelése */
void print_scale_values();

#endif