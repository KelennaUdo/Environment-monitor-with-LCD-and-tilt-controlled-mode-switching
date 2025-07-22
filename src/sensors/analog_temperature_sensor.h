#ifndef ANALOG_TEMPERATURE_SENSOR_H
#define ANALOG_TEMPERATURE_SENSOR_H

#include "base_sensor.h"
#include <math.h>

class AnalogTemperatureSensor : public Sensor {
public:
    AnalogTemperatureSensor(int pin) : Sensor(pin, TEMPERATURE_ANALOG) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("Analog temperature sensor pin not set. Cannot read temperature.");
            return;
        }
        
        const uint8_t oversample = 10;
        uint32_t sum = 0;
        for (uint8_t i = 0; i < oversample; i++) {
            sum += analogRead(pin);
        }
        float average = sum / (float)oversample;
        
        // Code from the kit manual
        float fenya = (average / 1023) * 5; 
        float r = (5 - fenya) / fenya * 4700; // Calculate the resistance of the thermistor
        
        value = (1 / (log(r / 10000) / 3950 + 1 / (25 + 273.15)) - 273.15); // Convert to Celsius using the Steinhart-Hart equation
    }
};

#endif