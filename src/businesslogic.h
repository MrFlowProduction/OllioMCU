#ifndef BUSINESSLOGIC_H /* include guards */
#define BUSINESSLOGIC_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <general/globals.h>
#include <general/enum.h>
#include <tools/lcd.h>
#include <tools/expander.h>
#include <tools/adc.h>
#include <tools/scale.h>
#include <tools/printer.h>
#include <general/types.h>
#include <tools/systools.h>
#include <tools/tap.h>

extern int m_counter;

/* Alapvető állapotkezelő */
void stateMachine();

/* Alapvető rendszer cuccok inicializálása */
void INIT_MACHINE();

#endif