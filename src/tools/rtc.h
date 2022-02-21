#define RTC_H
#ifdef RTC_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <general/pinout.h>
#include <general/globals.h>
#include <tools/diag.h>
#include <terminal.h>

void INIT_RTC();

/* Dátum beállítása */
void setDate(const DateTime&);

/* Idő lekérdezése */
DateTime now();

/* Hőmérséklet lekérdezése */
float rtcTemp();

/* Dátum kiíratása */
void showDate(const char*, const DateTime&); 

/* Dátum szöveg konverzió */
String dateToString(const DateTime dt);

/* Idő kiíratása */
void showTimeSpan(const char*, const TimeSpan&);

/* RTC frissítés NTP-ről */
void rtc_refresh();

#endif