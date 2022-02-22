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
#include <tools/tap.h>
#include <tools/expander.h>
#include <businesslogic.h>

void INIT_TERMINAL();



void terminal_handler();

void dateTimeTerminal();

#endif /* TERMINAL_H */