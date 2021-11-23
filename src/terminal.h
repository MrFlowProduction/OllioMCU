#ifndef TERMINAL_H /* include guards */
#define TERMINAL_H

#include <Arduino.h>            // Base Arduino library
#include <general/settings.h>           // Settings
#include <general/enum.h>
#include <general/globals.h>
#include <tools/printer.h>
#include <tools/mem.h>
#include <tools/systools.h>
#include <tools/rtc.h>

void INIT_TERMINAL();

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

void terminal_handler();

void dateTimeTerminal();

#endif /* TERMINAL_H */