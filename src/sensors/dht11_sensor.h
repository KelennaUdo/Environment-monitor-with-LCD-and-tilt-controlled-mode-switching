#ifndef DHT11_SENSOR_H
#define DHT11_SENSOR_H

#include "base_sensor.h"
#include <dht11.h>

class DHT11Sensor : public Sensor {
private:
    dht11 dht11_sensor;
    float humidity_value;

public:
    DHT11Sensor(int pin) : Sensor(pin, TEMPERATURE_DHT11), humidity_value(0.0) {}
    
    void read() override {
        if (!isValid()) {
            Serial.println("DHT11 pin not set. Cannot read temperature.");
            return;
        }
        dht11_sensor.read(pin);
        value = dht11_sensor.temperature;
        humidity_value = dht11_sensor.humidity;
    }
    
    float getHumidity() const { return humidity_value; }
};

#endif