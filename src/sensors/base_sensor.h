#ifndef BASE_SENSOR_H
#define BASE_SENSOR_H

#include <Arduino.h>

enum SensorType {
    TEMPERATURE_DHT11,
    TEMPERATURE_LINEAR,
    TEMPERATURE_ANALOG,
    HUMIDITY,
    LIGHT,
    GAS
};

class Sensor {
protected:
    int pin;
    float value;
    SensorType type;

public:
    // Constructor
    Sensor(int sensorPin, SensorType sensorType) : pin(sensorPin), value(0.0), type(sensorType) {}
    
    // Virtual destructor
    virtual ~Sensor() {}
    
    // Pure virtual methods that must be implemented by derived classes
    virtual void read() = 0;
    virtual float getValue() const { return value; }
    virtual SensorType getType() const { return type; }
    virtual bool isValid() const { return pin != -1; }
    
    // Common pin getter
    int getPin() const { return pin; }
};

#endif