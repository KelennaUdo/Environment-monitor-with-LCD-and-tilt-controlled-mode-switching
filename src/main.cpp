#include <Arduino.h>
#include <accelerometer.h>
#include <Wire.h>


Accelerometer accelerometer;
void setup() {
  Serial.begin(9600);

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
  // Initialize the accelerometer
  accelerometer.initialize(SCALE_2G, ODR_200);
}

void loop() {

  accelerometer.read_if_available(); // Check if new data is available and read it
  // accelerometer.print_binary_accelerations(); // Print raw accelerometer data in binary
  accelerometer.print_calculated_accelerations(); // Print calculated accelerations in g's
  accelerometer.print_orinetation(); // Print the current orientation
  delay(500); // Wait for a second before the next loop iteration

}