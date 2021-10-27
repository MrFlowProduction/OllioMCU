#ifndef SETTINGS_H /* include guards */
#define SETTINGS_H

// _______________________________________ Settings ____________________________________________
// =============================================================================================
//      NAME                VALUE                   DESCRIPTION
// =============================================================================================
#define BAUDRATE            115600                  // Meas send interval in minute(s)
#define MEAS_TIME           10000                   // Méréshez szükséges idő (ms)  
#define QLTY_VOLTAGE        1.5                     // Olaj minimum minőség (Voltban)
#define NO_LIQUID_VOLT      0.5                     // Olaj minimum minőség (Voltban)
#define SEPARATE_TIMEOUT    30000                   // Szeparálás időzítése
#define SCALE_SAMPLE        20                      // Mérleg mintavétel
#define BLOCK_NUMBER        10000                   // Kezdő blokk azonosító
#define VERSION             "build 1.0.101a"        // Verziószám
#define CREATOR             "by Mr.Flow Production" // Készítő
#define TAP_CLOSED          0                       // Csap csukott állapotának szöge
#define TAP_WATERTANK       90                      // Csap víztartáj felé nyitott szöge
#define TAP_BARREL          180                     // Csap hordó irányába nyitott állapotának szöge
#define TAP_ANGLE_HIST      2                       // Csap szögeltérésének plusz-minusz e-ngedélye
#define TAP_TIMEOUT         10000                   // Csap időtúllépése arra az esetre ha megszorulna vagy a motor nem reagálna
// =============================================================================================





#endif