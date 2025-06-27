# Environment Monitor with LCD and Tilt-Controlled Mode Switching

This project is the first step in building an Arduino-based environment monitoring system. The final goal is to display environmental data on an LCD screen and allow users to switch between different display or operation modes by tilting the device, using an onboard accelerometer for intuitive, button-free control.

## Current Status

**Stage 1:**  
- Reads data from an MMA8452Q accelerometer (connected via I2C).
- Logs raw and calculated acceleration values, as well as device orientation, to the serial monitor.
- The code is written using an object-oriented programming (OOP) paradigm for modularity and future extensibility.

**Stage 2:**  
- Introduced a finite state machine (FSM) to manage different operation modes.
- The device now switches modes based on orientation readings from the accelerometer, enabling tilt-based mode switching.

## Features (Current)

- I2C device scanning and initialization
- Real-time accelerometer data logging (X, Y, Z axes)
- Orientation detection (portrait/landscape/flat)
- OOP-based code structure
- FSM-based mode switching using accelerometer orientation

## Next Steps

- Integrate environmental sensors (e.g., temperature, humidity)
- Add LCD display for data output
- Expand FSM to handle more complex interactions

## Getting Started

1. Connect the MMA8452Q accelerometer to your Arduino (SDA to A4, SCL to A5, VCC, and GND).
2. Upload the code using PlatformIO or Arduino IDE.
3. Open the serial monitor at 9600 baud to view accelerometer data and orientation.

## License

MIT