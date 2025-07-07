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
    uint32_t sum = 0;
    for (uint8_t i = 0; i < oversample; i++) {
        sum += analogRead(linear_temp_sensor_pin);
    }
    int rawADC = sum / oversample;


  // Convert ADC reading to voltage (assuming 5V reference)
    float voltage = rawADC * (5.0 / 1023.0);  // in volts

  // Convert voltage to temperature (°C)
    temperature_linear_temp_sensor = (voltage * 100.0)-273.15;     // 10mV per °C → V * 100


}

void sensors::read_temperature_analog_temp_sensor() {
    if (analog_temp_sensor_pin == -1) {
        Serial.println("Analog temperature sensor pin not set. Cannot read temperature.");
        return;
    }

    const uint8_t oversample = 10;
    const float vRef = 5.0; // Assuming 5V reference
    const int adcMax = 1023;

    // Thermistor parameters
    const float seriesResistor = 10000.0; // 10kΩ series resistor
    const float nominalResistance = 10000.0; // 10kΩ at 25°C
    const float nominalTemperature = 25.0; // 25°C
    const float bCoefficient = 3950.0; // Beta coefficient

    uint32_t sum = 0;
    for (uint8_t i = 0; i < oversample; i++) {
        sum += analogRead(analog_temp_sensor_pin);
    }

    float average = sum / (float)oversample;
    float voltage = (average * vRef) / adcMax;
    float resistance = seriesResistor * ((vRef / voltage) - 1.0);

    // Steinhart-Hart equation
    float steinhart;
    steinhart = resistance / nominalResistance;     // (R/Ro)
    steinhart = log(steinhart);                     // ln(R/Ro)
    steinhart /= bCoefficient;                      // 1/B * ln(R/Ro)
    steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                    // Invert
    steinhart -= 273.15;                            // Convert to °C

    // Calibration offset (measured error: reading is ~27°C too high)
    // Adjust this value based on your calibration measurements
    // const float calibration_offset = -27.0;
    temperature_analog_temp_sensor = steinhart;

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