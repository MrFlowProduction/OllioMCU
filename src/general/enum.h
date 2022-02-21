#ifndef ENUM_H /* include guards */
#define ENUM_H

// General Enums
#define UNKONWN 0
#define OFF     0
#define ON      1
#define ENABLE  1
#define DISABLE 0


/* DC Motor állapotai */
enum MotorState {
    STOP,
    BRAKE,
    FORWARD,
    BACKWARD
};


/* Tap State */
enum TapState {
    WATERTANK,
    CLOSE,
    BARREL
};


/* Machine State */
enum MachineState {
    NONE,
    DEF,
    START,
    SERVICE,
    DEMO,
    FAULT,
    SHORTING,
    SEPARATE,
    MEASURE,
    PRINTING,
    SYSCHECK,
    CLOSING
};


enum WifiState {
    NOWIFI,
    CONNECTING,
    CONNECTED,
    DISCONNECTED,
    NORADIO
};


// Error codes
#define ERROR_NONE 1000
#define ERROR_DOOR_SENSOR_OPEN 1010
#define ERROR_LCD 1020
#define ERROR_PRINTER_INIT 1030
#define ERROR_PRINTER_PAPER 1031
#define ERROR_PRINTER_INK 1032
#define ERROR_ADC 1040
#define ERROR_SCALE 1050
#define ERROR_TANK_SENSOR 1060
#define ERROR_MOTOR 1070
#define ERROR_RTC 1080
#define ERROR_RTC_LOST_POWER 1081

#endif