#include "sensors.h"

sensors::sensors(){}
// Overloaded constructor for all sensors
sensors::sensors(int dht11, int linear_temp, int analog_temp, int light, int gas): dht11_pin(dht11), 
linear_temp_sensor_pin(linear_temp), analog_temp_sensor_pin(analog_temp), light_pin(light), gas_pin(gas) {}

sensors::sensors(int dht11, int linear_temp, int analog_temp): dht11_pin(dht11), 
linear_temp_sensor_pin(linear_temp), analog_temp_sensor_pin(analog_temp){}
sensors::~sensors() {
    // Destructor can be used for cleanup if needed
}

void sensors::read_temperature_dht11 (){
    if (dht11_pin == -1) {
        Serial.println("DHT11 pin not set. Cannot read temperature.");
        return;
    }
    dht11_sensor.read(dht11_pin);
    temperature_dht11 = dht11_sensor.temperature;
}

void sensors::read_temperature_linear_temp_sensor() {
    if (linear_temp_sensor_pin == -1) {
        Serial.println("Linear temperature sensor pin not set. Cannot read temperature.");
        return;
    }

    const uint8_t oversample = 10;
    const float vRef = 5.0; // Assuming you're using 5V AREF

    uint32_t sum = 0;
    for (uint8_t i = 0; i < oversample; i++) {
        sum += analogRead(linear_temp_sensor_pin);
    }

    float average = sum / (float)oversample;
    float voltage = (average * vRef) / 1023.0;

    // TMP36: 500mV = 0°C, 10mV per °C
    temperature_linear_temp_sensor = (voltage - 0.5) * 100.0;


}

void sensors::read_temperature_analog_temp_sensor() {
    if (analog_temp_sensor_pin == -1) {
        Serial.println("Analog temperature sensor pin not set. Cannot read temperature.");
        return;
    }

    const uint8_t oversample = 10;
    const float vRef = 5.0; // 5V reference

    uint32_t sum = 0;
    for (uint8_t i = 0; i < oversample; i++) {
        sum += analogRead(analog_temp_sensor_pin);
    }

    float average = sum / (float)oversample;
    float voltage = (average * vRef) / 1023.0;

    // TMP36: 0.5V offset, 10mV per °C
    temperature_analog_temp_sensor = (voltage - 0.5) * 100.0;

}


void sensors::read_humidity() {
    if (dht11_pin == -1) {
        Serial.println("Humidity pin not set. Cannot read humidity.");
        return;
    }
    dht11_sensor.read(dht11_pin);
    humidity = dht11_sensor.humidity;
}

void sensors::read_light() {
    if (light_pin == -1) {
        Serial.println("Light pin not set. Cannot read light.");
        return;
    }
    light = analogRead(light_pin); // Read light level from analog pin
}

void sensors::read_gas() {
    if (gas_pin == -1) {
        Serial.println("Gas pin not set. Cannot read gas level.");
        return;
    }
    gas = analogRead(gas_pin); // Read gas level from analog pin
    if(gas > 300) { // You can adjust this threshold
        Serial.println("Gas Detected!");
    } else {
        Serial.println("No Gas Detected.");
    }
}