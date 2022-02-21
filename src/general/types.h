#ifndef TYPES_H /* include guards */
#define TYPES_H

#include <Arduino.h>



/* Egy mérés összes adata */
struct Measurement
{
    float quality;
    float weight;
    bool isGoodQuality;
};





#endif