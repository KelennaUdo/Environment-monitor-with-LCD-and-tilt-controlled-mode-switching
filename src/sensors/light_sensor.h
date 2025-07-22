#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "base_sensor.h"

class LightSensor : public Sensor {
public:
    LightSensor(int pin) : Sensor(pin, LIGHT) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("Light pin not set. Cannot read light.");
            return;
        }
        value = analogRead(pin); // Read light level from analog pin
    }
};

#endif