# Sensor Class Polymorphic Architecture

## Overview
The sensor system has been restructured to implement polymorphism with a parent sensor class that all other sensors inherit from. This provides better code organization, extensibility, and follows object-oriented programming principles.

## Architecture

### Base Sensor Class (`base_sensor.h`)
- **Abstract base class** with pure virtual methods
- Defines common interface for all sensors
- Contains common attributes: `pin`, `value`, `type`
- Provides virtual methods: `read()`, `getValue()`, `getType()`, `isValid()`

### Individual Sensor Classes
Each sensor type now has its own dedicated class:

1. **DHT11Sensor** (`dht11_sensor.h`)
   - Inherits from `Sensor`
   - Handles DHT11 temperature readings
   - Also stores humidity value accessible via `getHumidity()`

2. **LinearTemperatureSensor** (`linear_temperature_sensor.h`)
   - Inherits from `Sensor`
   - Handles linear temperature sensor readings
   - Uses oversampling for accuracy

3. **AnalogTemperatureSensor** (`analog_temperature_sensor.h`)
   - Inherits from `Sensor`
   - Handles thermistor-based temperature readings
   - Uses Steinhart-Hart equation for conversion

4. **HumiditySensor** (`humidity_sensor.h`)
   - Inherits from `Sensor`
   - Dedicated humidity readings from DHT11
   - Separate from temperature for clear separation of concerns

5. **LightSensor** (`light_sensor.h`)
   - Inherits from `Sensor`
   - Handles light level readings from analog pin

6. **GasSensor** (`gas_sensor.h`)
   - Inherits from `Sensor`
   - Handles gas detection with threshold checking

### Composite Sensors Class (`sensors.h/cpp`)
The main `sensors` class now uses composition instead of monolithic implementation:
- Contains individual sensor instances as smart pointers
- Maintains **backward compatibility** with existing API
- Provides new polymorphic interface methods

## Key Benefits

### 1. Polymorphism
```cpp
// Example: Use any sensor polymorphically
std::vector<std::unique_ptr<Sensor>> sensorCollection;
sensorCollection.push_back(std::make_unique<DHT11Sensor>(2));
sensorCollection.push_back(std::make_unique<LightSensor>(5));

for (auto& sensor : sensorCollection) {
    sensor->read();  // Polymorphic call
    float value = sensor->getValue();
    SensorType type = sensor->getType();
}
```

### 2. Extensibility
Adding new sensor types is now simple:
1. Create new class inheriting from `Sensor`
2. Implement the `read()` method
3. Add to `SensorType` enum if needed

### 3. Memory Safety
- Uses `std::unique_ptr` for automatic memory management
- No manual memory allocation/deallocation required

### 4. Type Safety
- `SensorType` enum provides compile-time type checking
- Clear identification of sensor types

## Backward Compatibility

The existing main.cpp code works **without any changes**:

```cpp
// Original code still works exactly the same
envSensors.read_temperature_dht11();
envSensors.read_temperature_linear_temp_sensor();
float temp = envSensors.get_temperature_dht11();
float humidity = envSensors.get_humidity();
```

## New Polymorphic Interface

### Reading All Sensors
```cpp
// New method: read all sensors at once
envSensors.readAllSensors();

// Get all sensor objects for polymorphic operations
auto allSensors = envSensors.getAllSensors();
for (Sensor* sensor : allSensors) {
    sensor->read();
    Serial.print("Sensor value: ");
    Serial.println(sensor->getValue());
}
```

### Example Usage
See `sensor_demo.cpp` for complete examples of:
- Polymorphic sensor collections
- Type-safe sensor iteration
- Mixed sensor type handling

## Usage Examples

### Traditional Usage (Backward Compatible)
```cpp
sensors envSensors(2, 1, 2, 5, 0); // DHT11, Linear, Analog, Light, Gas

// Read specific sensors
envSensors.read_temperature_dht11();
envSensors.read_light();

// Get values
float temp = envSensors.get_temperature_dht11();
float light = envSensors.get_light();
```

### New Polymorphic Usage
```cpp
sensors envSensors(2, 1, 2, 5, 0);

// Read all sensors polymorphically
envSensors.readAllSensors();

// Process all sensors uniformly
auto allSensors = envSensors.getAllSensors();
for (Sensor* sensor : allSensors) {
    switch (sensor->getType()) {
        case TEMPERATURE_DHT11:
            Serial.println("Temperature from DHT11");
            break;
        case LIGHT:
            Serial.println("Light level");
            break;
        // ... other cases
    }
}
```

## File Structure
```
src/sensors/
├── base_sensor.h              # Abstract base class
├── dht11_sensor.h             # DHT11 temperature sensor
├── linear_temperature_sensor.h # Linear temperature sensor
├── analog_temperature_sensor.h # Analog temperature sensor
├── humidity_sensor.h          # Humidity sensor
├── light_sensor.h             # Light sensor
├── gas_sensor.h               # Gas sensor
├── sensors.h                  # Main composite sensors class
├── sensors.cpp                # Implementation
├── sensor_demo.h              # Demo functions header
└── sensor_demo.cpp            # Polymorphism examples
```

## Advantages of This Design

1. **Single Responsibility**: Each sensor class has one responsibility
2. **Open/Closed Principle**: Open for extension, closed for modification
3. **Liskov Substitution**: Any sensor can be used wherever `Sensor*` is expected
4. **Dependency Inversion**: High-level code depends on abstractions
5. **Maintainability**: Easy to modify individual sensor behavior
6. **Testability**: Each sensor class can be tested independently