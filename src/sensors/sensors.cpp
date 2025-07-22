#include "sensors.h"

sensors::sensors(){}

// Overloaded constructor for all sensors
sensors::sensors(int dht11, int linear_temp, int analog_temp, int light, int gas) {
    if (dht11 != -1) {
        dht11_temp_sensor = std::make_unique<DHT11Sensor>(dht11);
        humidity_sensor = std::make_unique<HumiditySensor>(dht11);
    }
    if (linear_temp != -1) {
        linear_temp_sensor = std::make_unique<LinearTemperatureSensor>(linear_temp);
    }
    if (analog_temp != -1) {
        analog_temp_sensor = std::make_unique<AnalogTemperatureSensor>(analog_temp);
    }
    if (light != -1) {
        light_sensor = std::make_unique<LightSensor>(light);
    }
    if (gas != -1) {
        gas_sensor = std::make_unique<GasSensor>(gas);
    }
}

sensors::sensors(int dht11, int linear_temp, int analog_temp) {
    if (dht11 != -1) {
        dht11_temp_sensor = std::make_unique<DHT11Sensor>(dht11);
        humidity_sensor = std::make_unique<HumiditySensor>(dht11);
    }
    if (linear_temp != -1) {
        linear_temp_sensor = std::make_unique<LinearTemperatureSensor>(linear_temp);
    }
    if (analog_temp != -1) {
        analog_temp_sensor = std::make_unique<AnalogTemperatureSensor>(analog_temp);
    }
}

sensors::~sensors() {
    // Smart pointers will automatically clean up
}

// Backward compatible read methods
void sensors::read_temperature_dht11() {
    if (dht11_temp_sensor) {
        dht11_temp_sensor->read();
    }
}

void sensors::read_temperature_linear_temp_sensor() {
    if (linear_temp_sensor) {
        linear_temp_sensor->read();
    }
}

void sensors::read_temperature_analog_temp_sensor() {
    if (analog_temp_sensor) {
        analog_temp_sensor->read();
    }
}

void sensors::read_humidity() {
    if (humidity_sensor) {
        humidity_sensor->read();
    }
}

void sensors::read_light() {
    if (light_sensor) {
        light_sensor->read();
    }
}

void sensors::read_gas() {
    if (gas_sensor) {
        gas_sensor->read();
    }
}

// Backward compatible getter methods
float sensors::get_temperature_dht11() const {
    return dht11_temp_sensor ? dht11_temp_sensor->getValue() : 0.0;
}

float sensors::get_temperature_linear_temp_sensor() const {
    return linear_temp_sensor ? linear_temp_sensor->getValue() : 0.0;
}

float sensors::get_temperature_analog_temp_sensor() const {
    return analog_temp_sensor ? analog_temp_sensor->getValue() : 0.0;
}

float sensors::get_humidity() const {
    return humidity_sensor ? humidity_sensor->getValue() : 0.0;
}

float sensors::get_light() const {
    return light_sensor ? light_sensor->getValue() : 0.0;
}

float sensors::get_gas() const {
    return gas_sensor ? gas_sensor->getValue() : 0.0;
}

std::vector<float> sensors::get_all_temperatures() const {
    return {get_temperature_dht11(), get_temperature_linear_temp_sensor(), get_temperature_analog_temp_sensor()};
}

float sensors::get_average_temperature() const {
    float sum = get_temperature_dht11() + get_temperature_linear_temp_sensor() + get_temperature_analog_temp_sensor();
    return sum / 3.0;
}

// New polymorphic interface methods
std::vector<Sensor*> sensors::getAllSensors() const {
    std::vector<Sensor*> sensorList;
    if (dht11_temp_sensor) sensorList.push_back(dht11_temp_sensor.get());
    if (linear_temp_sensor) sensorList.push_back(linear_temp_sensor.get());
    if (analog_temp_sensor) sensorList.push_back(analog_temp_sensor.get());
    if (humidity_sensor) sensorList.push_back(humidity_sensor.get());
    if (light_sensor) sensorList.push_back(light_sensor.get());
    if (gas_sensor) sensorList.push_back(gas_sensor.get());
    return sensorList;
}

void sensors::readAllSensors() {
    auto sensorList = getAllSensors();
    for (auto sensor : sensorList) {
        sensor->read();
    }
}