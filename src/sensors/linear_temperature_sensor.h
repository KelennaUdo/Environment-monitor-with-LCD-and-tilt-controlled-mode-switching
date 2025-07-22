#ifndef LINEAR_TEMPERATURE_SENSOR_H
#define LINEAR_TEMPERATURE_SENSOR_H

#include "base_sensor.h"

class LinearTemperatureSensor : public Sensor {
public:
    LinearTemperatureSensor(int pin) : Sensor(pin, TEMPERATURE_LINEAR) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("Linear temperature sensor pin not set. Cannot read temperature.");
            return;
        }
        const uint8_t oversample = 10;
        uint32_t sum = 0;
        for (uint8_t i = 0; i < oversample; i++) {
            sum += analogRead(pin);
        }
        uint32_t rawADC = sum / oversample;
        // Code from the kit manual
        value = (500 * rawADC) / 1024;
    }
};

#endif