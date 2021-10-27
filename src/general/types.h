#ifndef TYPES_H /* include guards */
#define TYPES_H

#include <Arduino.h>



/* Egy mérés összes adata */
typedef struct Measurement
{
    float quality;
    float weight;
    bool isGoodQuality;
} Measurement;





#endif