#ifndef SETTINGS_H /* include guards */
#define SETTINGS_H

// _______________________________________ Settings ____________________________________________
// =============================================================================================
//      NAME                VALUE                   DESCRIPTION
// =============================================================================================
#define BAUDRATE            115600                  // Meas send interval in minute(s)
#define MEAS_TIME           10000                    // Méréshez szükséges idő (ms)  
#define QLTY_VOLTAGE        1.5                     // Olaj minimum minőség (Voltban)
#define NO_LIQUID_VOLT      0.5                     // Olaj minimum minőség (Voltban)
#define SEPARATE_TIMEOUT    30000                   // Szeparálás időzítése
#define SCALE_SAMPLE        20                       // Mérleg mintavétel
#define BLOCK_NUMBER        10000                   // Kezdő blokk azonosító
#define VERSION             "build 1.0.101a"        // Verziószám
#define CREATOR             "by Mr.Flow Production" // Készítő
// =============================================================================================

#endif