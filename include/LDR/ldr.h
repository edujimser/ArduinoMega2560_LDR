#ifndef LDR_H
#define LDR_H


#include "System/pinout/pinout.h"

class LDR{
    private:
        PinInfo pin;
    public:
        LDR(PinInfo pin) : pin(pin) {}
    
    int read();

};




#endif // LDR_H