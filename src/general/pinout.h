#ifndef PINOUT_H /* include guards */
#define PINOUT_H

// ===============================================================================
//      NAME                    PIN            DESCRIPTION
// ===============================================================================
#define LED                     19          // Built-in LED
#define HX711_SCK               33          // Clock
#define HX711_DAT               25          // DATA
#define NEO_PIXEL               26          // NEO Pixel LED
#define EXP_INTB                5           // Expander Interrupt Pin
// ===============================================================================

// Expander Pinout
// ===============================================================================
//      NAME                    PIN          DESCRIPTION
// ===============================================================================
#define BUTTON_LED              4         // Button backlight (OUT1)
#define SERVICE_LED             5         // Serivce button backlight (OUT2)
#define TANK_SENSOR             0         // Tank full sensor (IN1)
#define USER_BUTTON             1         // User control button    (IN2)
#define DOOR_SENSOR             2         // Door sensor input  (IN3)
#define SERVICE_BUTTON          3         // Service button input  (IN4)
#define DC_EN                   8         // DC Motor EN   
#define DC_IN1                  10        // DC Motor H-Bridge IN1
#define DC_IN2                  9         // DC Motor H-Bridge IN2
#define PROBE_SUPPLY            11        // Szonda tápfeszültség (IO1)
#define ESW_OPENED              12        // Végállás nyitva    (IO2)
#define ESW_CLOSED              13        // Végállás csukva    (IO3)

// ===============================================================================

// ADS1115 ADC
// ===============================================================================
//      NAME                    PIN          DESCRIPTION
// ===============================================================================
#define PROBE_PIN               0         // Olajban áztatott szonda
#define TAP_PIN                 1         // Csap elfordulás érzékelője (potmétere)
// ===============================================================================

// Serial 2
#define RXD2 16
#define TXD2 17

#endif