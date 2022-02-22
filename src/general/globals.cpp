#include <general/globals.h>
// ____________________________________________ Globals ___________________________________________________
// ========================================================================================================
// TYPE             NAME                    DEF. VALUE         DESCRIPTION
// ========================================================================================================
char*               ssid =                  "Anna & Flori"; // Router SSID
char*               pass =                  "pO5NNrc6";     // Router Password
bool                terminal_enabled =      true;           // Terminal enabled
bool                wifi_connected =        false;          // Wifi is connected
bool                isExpanderReady =       false;          // MCP23017 I/O Expander Module is ready to use
bool                isAdcReady =            false;          // ADS1115 ADC Module is ready to use
bool                isScaleReady =          false;          // HX711 ADC Module is ready to use
volatile bool       isButtonPressed =       false;          // User button pressed and not handled
volatile bool       isTankFull =            false;          // Tank is fullfilled
volatile bool       isDoorOpened =          false;          // Fedél állapota
volatile bool       isDoorChanged =         false;          // Fedél állapota megváltozott (és még nincs kezelve)
bool                isServiceButtonPressed = false;
unsigned long       globalTimer =           0;              // Globális időzítő változó, mindenféle időméréshez
float               scaleReferencePoint =   0;              // Mérleg referenciapont
TapState            tapState;                               // Current tap state
MachineState        statePoint =            NONE;           // Current machine State
bool                stateChanged =          false;          // State changed flag
float               probe_votlage;                          // Current probe voltage
float               progress;                               // Current progress state in percent
float               last_meas =             0;              // Legutolsó lemért olaj mennyisége
int                 block_id =              1000;           // Blokk azonosító (inkrementálni kell)
Measurement         meas;
bool                isRtcOk =               true;           // RTC frissítve
bool                stateTempVariable =     false;
// Screen
// ========================================================================================================
unsigned long       screen_update_timer =   0;              // Kijelző frissítés időzítője
byte                screen_state =          0;              // Állapot tároló
byte                screen_max_state_number;                // Kijelző max állapot
uint                screen_state_delay =    0;              // Kijelző állapotváltás intervellaum (ha 0 akkor nincs változás)
bool                screen_first_update =   true;          // Kijelző első frissítése
// Oil values
// ========================================================================================================
float               oilquality_max =        10;             // Oil quality max value
float               oilquality_min =        5;              // Oil quality max value
// Scale values
// ========================================================================================================
float               scale_value;                            // Scale measured value
bool                task_scale_isEnabled;                   // Scale task enabling
bool                task_ads_isEnabled;                     // ASD task enabling
volatile byte       error_code =            0;              // Hibakód
//int                 machineState =          SEPARATE;
// ========================================================================================================

bool                blink;

// WIFI
// ========================================================================================================
WifiState           wifiStat = WifiState::NOWIFI;
bool                wifiIsConnected =       false;
bool                wifiStateHandled =      true;

// TAP
// ========================================================================================================
int                 tap_closed_angle =      0;              // Csap zárt állapotának szöge
int                 tap_barrel_angle =      120;            // Csap hordó fele álló szöge
int                 tap_watertank_angle =   230;            // Csap víztartály felé nyíló szöge
bool                tap_init_en =           false;          // Csap initkor alaphelyzetbe állítás engedélyezve van-e


// SCALE
// ========================================================================================================
float               scale_calib_factor =    56.0;           // Mérleg kalibrációs értéke
float               scale_zero_pointer =    0.0;            // Mérleg null pontja
long                scale_last_offset =     0;              // Mérleg legutóbbi offsetje, a hordó zéró pointja
