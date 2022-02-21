#ifndef DIAG_H /* include guards */
#define DIAG_H

#include <Arduino.h>
#include <tools/lcd.h>

void printSysData(char*);

void printtestpassed();

void printtestfailed();

void printready();

void printdone();

void printfail();

void printok();

void printerror();

void printinit(String, bool = false);

void printreason(String, bool = false);


/* Rendszerhiba dobása, üzemképtelen állapot */
void dropFaulty(String, int, bool = true);

/* Rendszerellenőrzés */
void syscheck();

#endif /* DIAG_H */