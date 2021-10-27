#ifndef EXPANDER_H /* include guards */
#define EXPANDER_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <terminal.h>
#include <tools/systools.h>
#include <general/pinout.h>
#include <general/globals.h>
#include <tools/diag.h>
#include <general/enum.h>

extern Adafruit_MCP23017 mcp;

extern bool isMcpConnected;
extern volatile bool isButtonPressed;

/* Init expander */
void INIT_EXTERNAL_PORTS();

/* Handling Interrupts 
void handlingExpInterrupt(); */

/* Állapotok regisztrálása */
void InitExpanderStates();

/* DC motor vezérlés */
void setDcMotorPins(bool, bool, bool);

/* Felhasználói gomb háttérvilágítása */
void setButtonLight(bool);

/* Szerviz gomb háttérvilágítása */
void setServiceLight(bool);

/* Reads a digital input */
int getSensValue(int);

/* Szonda anód tápfeszültség kapcsolása */
void setProbeSupply(bool);

/* Csap beállítása */
void SetTap(TapState);



bool doorOpened();

bool tankState();

bool userButton();

bool serviceButton();

#endif