#ifndef LDR_H
#define LDR_H


#include "System/pinout/pinout.h"

class LDR{
    private:
        const PinInfo pin;

        // Var Time -->
        unsigned long lastTimeChange = 0;
        unsigned long currentTime = 0;
        unsigned int  ValueAfterTime  = 0;


        //Buffer filter -->
        static const int bufferSize = 50;
        int buffer[bufferSize] = {0};
        int bufferIndex = 0;
        bool bufferFilled = false;

        //EMA filter -->
        float emaValue = 0;

        //Median filter -->
        const static int windowSize = 40;  
        int readings[windowSize];
        int index = 0;

        //Kalman filter -->
        float x_hat = 0;
        float p = 1;
        
    public:
        explicit LDR(const PinInfo& pin);
        /* -------------------------------------------------------------------------- */
        /*                               Read light level methods                     */           
        /* -------------------------------------------------------------------------- */
        int getRead(unsigned long delayTimeMillis); 
        int getReadWhitBuffer(unsigned long delayTimeMillis);
        int getReadEMA(float alpha, unsigned long delayTimeMillis);
        int getMedianReading();
        float getKalmanFilter(float q, float r);
};




#endif // LDR_H