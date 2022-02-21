#ifndef LCD_H /* include guards */
#define LCD_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

extern int prevMachineState;

/* Init LCD screen */
void INIT_LCD();

/*  */
void printRow(byte, char, int);

/*  */
void printByteRow(byte, byte, int);

/* Percentage animation */
void percentAnimation(byte);

/* Printing animation */
void printingAnimation(byte);

/* Slide up animation */
void slideUpEffect();

/* Slide down animation */
void slideDownEffect();

/* Fedel lecsukasara figyelmeztető üzenet */
void closeDownScreen();

/* Kijelző törlése animációval */
void clearScreen();

/* Alap kijelző mutatása */
void defaultScreen();

/* Display device name and software version */
void setNoneScreen();

/* Display init screen */
void setStartScreen();

/* Alsó sorba szöveg kiírása */
void printTag(String);
 
/* Display analog measurements and its process feedback */
void setShortingScreen();

/* Szeparációs kijelző frissítése */
void updateSeparateScreen();

/* Osztályozás kijelző frissítése */
void updateShortingScreen();

/* Display if it is necessary to transfer the loaded unfavorable oil to the separation tank */
void setSeparateScreen();

/* Olaj sújához tartozó lemérés kijelző */
void setMeasureScreen();

/* Mérés kijelző frissítése */
void updateMeasureScreen();

/* Mérleg értékének frissítése */
void updateMeasure(float);

/* Blokknyomtatás kijelzője */
void setPrintingScreen();

/* Szervizképernyő mindenféle finomsággal */
void setServiceScreen();

/* Szervizképernyő frissítése */
void updateServiceScreen();

/* Display process termination and reset */
void setClosingScreen();

/* Display demo mode */
void setDemoScreen();

/* Display error screen */
void setFaultScreen(String, int);

/* Rendszerteszt képernyője */
void setSyscheckScreen();

/* Következő képernyőre váltás */
void setNextScreen();

#endif