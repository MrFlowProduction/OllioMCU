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


// Error codes
#define ERROR_NONE 0
#define ERROR_DOOR_SENSOR_OPEN 1
#define ERROR_LCD 2
#define ERROR_PRINTER_INIT 3
#define ERROR_PRINTER_PAPER 31
#define ERROR_PRINTER_INK 32
#define ERROR_ADC 4
#define ERROR_SCALE 5
#define ERROR_TANK_SENSOR 6
#define ERROR_MOTOR 7

#endif