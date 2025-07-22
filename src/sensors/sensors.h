#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <vector> // Include vector for storing multiple temperature readings
#include <memory> // Include for smart pointers
#include "base_sensor.h"
#include "dht11_sensor.h"
#include "linear_temperature_sensor.h"
#include "analog_temperature_sensor.h"
#include "humidity_sensor.h"
#include "light_sensor.h"
#include "gas_sensor.h"

class sensors
{
private:
    // Individual sensor instances using polymorphism
    std::unique_ptr<DHT11Sensor> dht11_temp_sensor;
    std::unique_ptr<LinearTemperatureSensor> linear_temp_sensor;
    std::unique_ptr<AnalogTemperatureSensor> analog_temp_sensor;
    std::unique_ptr<HumiditySensor> humidity_sensor;
    std::unique_ptr<LightSensor> light_sensor;
    std::unique_ptr<GasSensor> gas_sensor;
public:
    // Default constructor
    sensors();

    // Overloaded constructor for all sensors
    sensors(int dht11, int linear_temp, int analog_temp, int light, int gas);
    sensors(int dht11, int linear_temp, int analog_temp); // Constructor for temperature sensors only
    ~sensors();
    
    // Getter methods (maintaining backward compatibility)
    float get_temperature_dht11() const; 
    float get_temperature_linear_temp_sensor() const; 
    float get_temperature_analog_temp_sensor() const; 
    float get_humidity() const;       
    float get_light() const;             
    float get_gas() const;                 
    
    // Getter for temperature from different sensors
    std::vector<float> get_all_temperatures() const; 

    float get_average_temperature() const; 
    
    // Read methods (maintaining backward compatibility)
    void read_temperature_dht11(); 
    void read_temperature_linear_temp_sensor(); 
    void read_temperature_analog_temp_sensor(); 
    void read_humidity();    
    void read_light();       
    void read_gas();         
    
    // New polymorphic interface methods
    std::vector<Sensor*> getAllSensors() const;
    void readAllSensors();
};
#endif