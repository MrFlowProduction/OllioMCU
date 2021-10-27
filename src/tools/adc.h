#define ADC_H
#ifdef ADC_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <Wire.h>
#include <ADS1X15.h>
#include <general/globals.h>
#include <terminal.h>
#include <general/pinout.h>
#include <tools/diag.h>

extern ADS1115 ads;

/* INIT adc module */
void INIT_ADC();

/* Read probe voltage */
float readProbeVoltage();

/* Csap elfordálását adja vissza szögben */
int readTapAngle();

/* Csap jeladó feszültsége */
float readTapVoltage();

/* ADC reading */
void adc_reading();

#endif