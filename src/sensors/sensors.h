#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <vector> // Include vector for storing multiple temperature readings

class sensors
{
private:
    float temperature_dht11; // Variable to hold temperature data
    float temperature_linear_temp_sensor; // Variable to hold temperature from linear temperature sensor
    float temperature_analog_temp_sensor; // Variable to hold temperature from analog temperature sensor
    float humidity;    // Variable to hold humidity data
    float light;       // Variable to hold light data
    float gas;         // Variable to hold gas level data
public:
    sensors(/* args */);
    ~sensors();
    float get_temperature_dht11() const { return temperature_dht11; } // Getter for temperature
    float get_temperature_linear_temp_sensor() const { return temperature_linear_temp_sensor; } // Getter for linear temperature meter
    float get_temperature_analog_temp_sensor() const { return temperature_analog_temp_sensor; } // Getter for analog temperature meter
    // Getter for temperature from different sensors
    std::vector<float> get_all_temperatures() const { 
        return {temperature_dht11, temperature_linear_temp_sensor, temperature_analog_temp_sensor}; 
    } // Returns all temperatures in a vector

    float get_average_temperature() const { 
        return (temperature_dht11 + temperature_linear_temp_sensor + temperature_analog_temp_sensor) / 3.0; 
    } // Average temperature from all sensors
    float get_humidity() const { return humidity; }       // Getter for humidity
    float get_light() const { return light; }             // Getter for light
    float get_gas() const { return gas; }                 // Getter for gas level
    void read_temperature(); // Method to read temperature data
    void read_humidity();    // Method to read humidity data
    void read_light();       // Method to read light data
    void read_gas();         // Method to read gas level data
};

sensors::sensors(/* args */)
{
}

sensors::~sensors()
{
}




#endif