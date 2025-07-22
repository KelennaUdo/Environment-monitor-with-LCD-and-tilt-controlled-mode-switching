#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include "base_sensor.h"

class GasSensor : public Sensor {
public:
    GasSensor(int pin) : Sensor(pin, GAS) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("Gas pin not set. Cannot read gas level.");
            return;
        }
        value = analogRead(pin); // Read gas level from analog pin
        if (value > 300) { // You can adjust this threshold
            Serial.println("Gas Detected!");
        } else {
            Serial.println("No Gas Detected.");
        }
    }
};

#endif