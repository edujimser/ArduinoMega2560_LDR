#include <Arduino.h>
#include "LDR/ldr.h"

LDR::LDR(const PinInfo& pin) 
    : pin(pin) {

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

int LDR::read(unsigned long delayTime) {
    static unsigned long lastChange = 0;
    static unsigned int  lastValue  = 0;
    unsigned long now = millis();

    if (now - lastChange >= delayTime) {
        lastChange = now;
        return lastValue = analogRead(pin.number);
    };
    
    return lastValue;
};