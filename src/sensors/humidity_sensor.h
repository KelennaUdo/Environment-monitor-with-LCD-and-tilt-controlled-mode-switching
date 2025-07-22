#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "base_sensor.h"
#include <dht11.h>

class HumiditySensor : public Sensor {
private:
    dht11 dht11_sensor;

public:
    HumiditySensor(int pin) : Sensor(pin, HUMIDITY) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("Humidity pin not set. Cannot read humidity.");
            return;
        }
        dht11_sensor.read(pin);
        value = dht11_sensor.humidity;
    }
};

#endif