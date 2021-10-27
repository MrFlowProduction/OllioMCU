#ifndef GLOBALS_H /* include guards */
#define GLOBALS_H

#include <Arduino.h> /* we need arduino functions to implement this */
#include <general/enum.h>
#include <general/types.h>

// ____________________________________________ Globals ___________________________________________________
// ========================================================================================================
// TYPE                     NAME                    DEF. VALUE         DESCRIPTION
// ========================================================================================================
extern char                 wifi_ssid[]; // Router SSID
extern char                 wifi_pass[];     // Router Password
extern bool                 terminal_enabled;
extern bool                 wifi_connected;
extern bool                 isExpanderReady;
extern bool                 isAdcReady;
extern bool                 isScaleReady;
extern volatile bool        isButtonPressed;
extern volatile bool        isTankFull;
extern volatile bool        isDoorOpened;
extern volatile bool        isDoorChanged;
extern bool                 isServiceButtonPressed;
extern unsigned long        globalTimer;
extern float                scaleReferencePoint;
extern MachineState         statePoint;
extern TapState             tapState;
extern bool                 stateChanged;          
extern float                probe_votlage;
extern float                progress;
extern float                oilquality_max;
extern float                oilquality_min;
extern bool                 task_scale_isEnabled;
extern bool                 task_ads_isEnabled;
extern volatile byte        error_code;
extern bool                 blink;
extern float                last_meas;
extern char*                machinde_id;
extern int                  block_id;
extern unsigned long        screen_update_timer;
extern byte                 screen_state;
extern byte                 screen_max_state_number;
extern uint                 screen_state_delay;
extern bool                 screen_first_update;
extern Measurement          meas;

//extern int                  machineState;
// ========================================================================================================

#endif