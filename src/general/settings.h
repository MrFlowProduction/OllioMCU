#ifndef SETTINGS_H /* include guards */
#define SETTINGS_H

#include <general/globals.h>

// _______________________________________ Settings ____________________________________________
// =============================================================================================
//      NAME                VALUE                   DESCRIPTION
// =============================================================================================
#define BAUDRATE            115600                  // Meas send interval in minute(s)
#define MEAS_TIME           10000                   // Méréshez szükséges idő (ms)  
#define QLTY_VOLTAGE        1.5                     // Olaj minimum minőség (Voltban)
#define NO_LIQUID_VOLT      0.5                     // Olaj minimum minőség (Voltban)
#define SEPARATE_TIMEOUT    30000                   // Szeparálás időzítése
#define SCALE_SAMPLE        2                       // Mérleg mintavétel
#define BLOCK_NUMBER        10000                   // Kezdő blokk azonosító
#define VERSION             "build 1.0.112a"        // Verziószám
#define CREATOR             "by Mr.Flow Production" // Készítő
#define TAP_ANGLE_HIST      1                       // Csap szögeltérésének plusz-minusz e-ngedélye
#define TAP_TIMEOUT         20000                   // Csap időtúllépése arra az esetre ha megszorulna vagy a motor nem reagálna
#define WIFI_AP_SSID        "Ollio AP"              // AP módhoz a wifi név
#define RTC_REFRESH         3600                    // RTC automatikus frissítésének intervalluma másodpercben
// =============================================================================================





#endif