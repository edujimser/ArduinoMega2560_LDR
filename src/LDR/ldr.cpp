#include "LDR/ldr.h"

int LDR::read(){
    return analogRead(pin.number);
};