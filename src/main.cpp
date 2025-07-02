#include <Arduino.h>
#include <accelerometer/accelerometer.h>
#include <Wire.h>
#include <mode_switch/mode_switch.h>
#include <sensors/sensors.h>

Accelerometer accelerometer;

sensors envSensors(2, 3, 4,5,0); 
// Function to check the I2C connection
void check_wire_connection();

void setup() {
  Serial.begin(9600);
  check_wire_connection(); // Check I2C connection
  // Initialize the accelerometer
  accelerometer.initialize(SCALE_2G, ODR_200);
  modeSwitchBegin(); // Initialize the mode switch
}

void loop() {
  accelerometer.read_if_available(); // Read accelerometer data if available
  updateModeSwitch(accelerometer.getOrientation()); // Update the mode switch based on orientation

  switch (currentMode())
  {
      case TEMP:
        envSensors.read_temperature_dht11();
        envSensors.read_temperature_linear_temp_sensor();
        envSensors.read_temperature_analog_temp_sensor();
        Serial.print("DHT11 Temp: ");
        Serial.print(envSensors.get_temperature_dht11());
        Serial.print(" C, Linear Temp: ");
        Serial.print(envSensors.get_temperature_linear_temp_sensor());
        Serial.print(" C, Analog Temp: ");
        Serial.print(envSensors.get_temperature_analog_temp_sensor());
        Serial.print(" C, Avg: ");
        Serial.print(envSensors.get_average_temperature());
        Serial.println(" C");
        break;
      case HUMIDITY:
        envSensors.read_humidity();
        Serial.print("Humidity: ");
        Serial.print(envSensors.get_humidity());
        Serial.println(" %");
        break;
      case LIGHT:
        envSensors.read_light();
        Serial.print("Light: ");
        Serial.println(envSensors.get_light());
        break;
      case GAS:
        envSensors.read_gas();
        Serial.print("Gas: ");
        Serial.println(envSensors.get_gas());
        break;
      case NEUTRAL:
        Serial.println("/* idle message       */");
        break;
  }
  delay(500); // Wait for a second before the next loop iteration

}


void check_wire_connection(){
    // I2C Scanner
  Wire.begin();
  Serial.println("Scanning I2C bus...");
  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at 0x");
      Serial.println(address, HEX);
    }
  }
  Serial.println("I2C scan complete.");
}