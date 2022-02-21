#ifndef TAP_H /* include guards */
#define TAP_H

#include <Arduino.h>
#include <tools/adc.h>
#include <tools/expander.h>
#include <general/enum.h>
#include <general/globals.h>
#include <tools/diag.h>

/* Csap beállítása */
bool SetTap(TapState);

/* Csap inicializálása, állapot */
void INIT_TAP(void);


#endif