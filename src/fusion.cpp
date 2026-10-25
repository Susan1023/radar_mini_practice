#include "fusion.h"

Point selectPosition(
    Track radar,
    RadioPosition radio,
    double now ,
    double radioTtl
){
    double age = now - radio.lastSeen;
    if (radar.robotId==radio.robotId && age <= radioTtl && age>=0 )
    {
        return radio.position;
    }
    return radar.position;
}