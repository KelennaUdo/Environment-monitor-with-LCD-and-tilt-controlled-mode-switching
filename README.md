# Environment Monitor with LCD and Tilt-Controlled Mode Switching

This project is an Arduino-based environment monitoring system. The final goal is to display environmental data on an LCD screen and allow users to switch between different display or operation modes by tilting the device, using an onboard accelerometer for intuitive, button-free control.

## Current Status

**Stage 1:**  
- Reads data from an MMA8452Q accelerometer (connected via I2C).
- Logs raw and calculated acceleration values, as well as device orientation, to the serial monitor.
- The code is written using an object-oriented programming (OOP) paradigm for modularity and future extensibility.

**Stage 2:**  
- Introduced a finite state machine (FSM) to manage different operation modes.
- The device now switches modes based on orientation readings from the accelerometer, enabling tilt-based mode switching.

**Stage 3:**  
- Added a dedicated sensor class to manage readings from all five sensors (DHT11, linear temperature sensor, analog temperature sensor, light sensor, and gas sensor).
- The sensor class abstracts sensor initialization and data collection, simplifying the main program logic and improving code maintainability.

**Stage 4:**
- Added two physical buttons to enable bi-directional mode switching, allowing users to change modes manually in addition to tilt-based switching.
- The program now supports both button-based and accelerometer-based mode navigation for greater flexibility and accessibility.

## Features (Current)

- I2C device scanning and initialization
- Real-time accelerometer data logging (X, Y, Z axes)
- Orientation detection (portrait/landscape/flat)
- OOP-based code structure
- FSM-based mode switching using accelerometer orientation
- Centralized sensor management via a dedicated class
- Bi-directional mode switching using two physical buttons

## Next Steps

- Integrate LCD display for data output
- Expand FSM to handle more complex interactions
- Add calibration and error handling for sensors

## Getting Started

1. Connect the MMA8452Q accelerometer and all sensors to your Arduino (see code for pin assignments).
2. Connect two push buttons to the specified digital pins for manual mode switching.
3. Upload the code using PlatformIO or Arduino IDE.
4. Open the serial monitor at 9600 baud to view sensor data and orientation.

## License

MIT