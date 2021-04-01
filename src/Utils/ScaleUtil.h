#ifndef SCALE_H
#define SCALE_H

#include <Arduino.h>
#include "HX711.h"

class ScaleUtil
{
private:
    /* data */
public:
    const int LOADCELL_DOUT_PIN = D1;
    const int LOADCELL_SCK_PIN = D2;
    HX711 scale;
    float x = -9.85; //dây đen, out
                     //float x = -9.95; //dây đỏ, có gió
                     //float x = -10.07; //dây đỏ, ko gió
    ScaleUtil();
    ~ScaleUtil();
    float GetScale();
};

#endif
