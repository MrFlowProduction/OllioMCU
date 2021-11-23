#ifndef DIAG_H /* include guards */
#define DIAG_H

#include <Arduino.h>
#include <tools/lcd.h>

/* Rendszerhiba dobása, üzemképtelen állapot */
void dropFaulty(String, int, bool = true);

/* Rendszerellenőrzés */
void syscheck();

#endif /* DIAG_H */