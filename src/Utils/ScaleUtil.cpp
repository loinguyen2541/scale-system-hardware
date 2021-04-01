#include "ScaleUtil.h"

ScaleUtil::ScaleUtil()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(x);
    scale.tare();
}

ScaleUtil::~ScaleUtil()
{
}

float ScaleUtil::GetScale()
{
    float scalef = scale.get_units(10) / 1000;
    return scalef;
}