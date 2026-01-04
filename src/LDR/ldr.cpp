#include <Arduino.h>
#include "LDR/ldr.h"

LDR::LDR(const PinInfo& pinParam) 
    : pin(pinParam) {

    if (!isValidAnalog(pin)){
            Serial.println();
            Serial.print("LED Analog: Pin inválido -> ");
            Serial.print("name: ");   Serial.print(pin.name);
            Serial.print(", number: "); Serial.print(pin.number);
            Serial.print(", family: "); Serial.println(pin.family);
            
            Serial.println();
            Serial.println("System stopped due to critical error.");
            delay(100);
            cli();
            while (true) { __asm__("nop"); };};
}

int LDR::getRead(unsigned long delayTimeMillis) {

    currentTime = millis();

    //Difference between current time and previous reading time
    if ((currentTime - lastTimeChange) >= delayTimeMillis) {
        lastTimeChange = currentTime;
        return ValueAfterTime = analogRead(pin.number);
    };
    
    return ValueAfterTime;
};


int LDR::getReadWhitBuffer(unsigned long delayTimeMillis){
    currentTime = millis();

    //Difference between current time and previous reading time
 if ((currentTime - lastTimeChange) >= delayTimeMillis) {
        lastTimeChange = currentTime;

        //Buffer -->
        unsigned long sum = 0;
        buffer[bufferIndex] = analogRead(pin.number);

        int count = bufferFilled ? bufferSize : bufferIndex;  if (count == 0) count = 1; 
        
        for (int i = 0; i < count; i++){
            sum += buffer[i];
        }  

        bufferIndex++; if (bufferIndex >= bufferSize) { bufferIndex = 0; bufferFilled = true; };
        
        return ValueAfterTime = sum / count;
    };
    
    return ValueAfterTime;
}


int LDR::getReadEMA(float alpha, unsigned long delayTimeMillis){
    
    currentTime = millis();
    int current = analogRead(pin.number);

    if (emaValue == 0) {
        return current; 
    };    

     if (currentTime - lastTimeChange >= delayTimeMillis) {
        emaValue = alpha * current + (1 - alpha) * emaValue;
        return (int)emaValue;
    };

    return (int)emaValue;
}

int LDR::getMedianReading() {

    // Guardar nueva lectura en la ventana
    readings[index] = analogRead(pin.number);

    // Avanzar índice circular
    index = (index + 1) % windowSize;

    // Copiar los valores a un arreglo temporal
    int temp[windowSize];
    memcpy(temp,readings,sizeof(readings));

    // Ordenar el arreglo temporal (burbuja simple)
    for (int i = 0; i < windowSize - 1; i++) {
        for (int j = 0; j < windowSize - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    // Retornar el valor central (mediana)
    return temp[windowSize / 2];
}

float LDR::getKalmanFilter(float q, float r) {
    p = p + q;

    float k = p / (p + r);

    x_hat = x_hat + k * (analogRead(pin.number) - x_hat);

    p = (1 - k) * p;

    return x_hat;
}
