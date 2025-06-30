#include <Arduino.h>
#include <accelerometer/accelerometer.h>
#include <Wire.h>
#include <mode_switch/mode_switch.h>

Accelerometer accelerometer;

// Function to check the I2C connection
void check_wire_connection();

void setup() {
  Serial.begin(9600);
  // Initialize the accelerometer
  accelerometer.initialize(SCALE_2G, ODR_200);
  modeSwitchBegin(); // Initialize the mode switch
}

void loop() {
  accelerometer.read_if_available(); // Read accelerometer data if available
  updateModeSwitch(accelerometer.getOrientation()); // Update the mode switch based on orientation

  switch (currentMode())
  {
      case TEMP:     Serial.println("/* display temperature */"); break;
      case HUMIDITY:  Serial.println("/* display humidity   */"); break;
      case LIGHT:     Serial.println("/* display light      */"); break;
      case GAS:       Serial.println("/* display gas level  */"); break;
      case NEUTRAL:   Serial.println("/* idle message       */"); break;
  }
  // accelerometer.print_orinetation();
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