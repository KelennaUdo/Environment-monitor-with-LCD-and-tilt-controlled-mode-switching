#include "sensors.h"

// Example function demonstrating polymorphism
void demonstratePolymorphism() {
    // Create sensors using polymorphism
    std::vector<std::unique_ptr<Sensor>> sensor_collection;
    
    // Add different types of sensors to the collection
    sensor_collection.push_back(std::make_unique<DHT11Sensor>(2));
    sensor_collection.push_back(std::make_unique<LinearTemperatureSensor>(1));
    sensor_collection.push_back(std::make_unique<AnalogTemperatureSensor>(3));
    sensor_collection.push_back(std::make_unique<LightSensor>(5));
    sensor_collection.push_back(std::make_unique<GasSensor>(0));
    
    Serial.println("=== Polymorphic Sensor Reading Demo ===");
    
    // Use polymorphism to read all sensors
    for (auto& sensor : sensor_collection) {
        sensor->read();
        
        Serial.print("Sensor Type: ");
        Serial.print(static_cast<int>(sensor->getType()));
        Serial.print(", Pin: ");
        Serial.print(sensor->getPin());
        Serial.print(", Value: ");
        Serial.println(sensor->getValue());
    }
    
    Serial.println("=== End Demo ===");
}

// Example usage showing how to iterate through sensors polymorphically
void readAllSensorsPolymorphically(sensors& envSensors) {
    Serial.println("Reading all sensors using polymorphic interface:");
    
    auto allSensors = envSensors.getAllSensors();
    for (Sensor* sensor : allSensors) {
        sensor->read();
        
        const char* sensorTypeName = "";
        switch (sensor->getType()) {
            case TEMPERATURE_DHT11: sensorTypeName = "DHT11 Temperature"; break;
            case TEMPERATURE_LINEAR: sensorTypeName = "Linear Temperature"; break;
            case TEMPERATURE_ANALOG: sensorTypeName = "Analog Temperature"; break;
            case HUMIDITY: sensorTypeName = "Humidity"; break;
            case LIGHT: sensorTypeName = "Light"; break;
            case GAS: sensorTypeName = "Gas"; break;
        }
        
        Serial.print(sensorTypeName);
        Serial.print(" (Pin ");
        Serial.print(sensor->getPin());
        Serial.print("): ");
        Serial.println(sensor->getValue());
    }
}