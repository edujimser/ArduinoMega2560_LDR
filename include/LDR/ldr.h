#ifndef LDR_H
#define LDR_H


#include "System/pinout/pinout.h"

class LDR{
    private:
        const PinInfo pin;
    public:
        explicit LDR(const PinInfo& pin);

        int read(unsigned long delayTime);

};




#endif // LDR_H