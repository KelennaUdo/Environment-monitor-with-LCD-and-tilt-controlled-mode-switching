#include <Arduino.h>
#include <accelerometer/accelerometer.h>
#include <Wire.h>
#include <mode_switch/mode_switch.h>
#include <sensors/sensors.h>
#include <LiquidCrystal.h>

Accelerometer accelerometer;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // Initialize LCD with pins RS, E, D4, D5, D6, D7
sensors envSensors(2, 3, 4, 5,0); 
// Function to check the I2C connection
void check_wire_connection();
bool isButtonPressed(uint8_t button) {
  return digitalRead(button) == LOW; // Button pressed when pin reads LOW
}

const uint8_t button_dec = 6;
const uint8_t button_inc = 7;
bool button_dec_pressed = false;
bool button_inc_pressed = false;
bool button_dec_previous = false; // To track the previous state of button_dec
bool button_inc_previous = false; // To track the previous state of button_inc
bool debounceExpired(unsigned long lastChange, unsigned long debounceMs) {
  return (millis() - lastChange) > debounceMs;
}
unsigned long lastChangeDec = 0;   // debounce for DEC button
unsigned long lastChangeInc = 0;   // debounce for INC button

void setup() {
  Serial.begin(9600);
  check_wire_connection(); // Check I2C connection
  // Initialize the accelerometer
  accelerometer.initialize(SCALE_2G, ODR_200);
  modeSwitchBegin(); // Initialize the mode switch
  pinMode(button_dec, INPUT_PULLUP); // Set button_dec as input with pull-up resistor
  pinMode(button_inc, INPUT_PULLUP); // Set button_inc as input with pull-up resistor
}

void loop() {
  // Read button states
  button_dec_pressed = isButtonPressed(button_dec);
  button_inc_pressed = isButtonPressed(button_inc);


  if( button_dec_pressed && button_inc_pressed){ //check if both buttons are pressed
    Serial.println("both buttons pressed");
    return;
  }
  else if((button_dec_pressed || button_inc_pressed))
  {
      Serial.println("one button pressed");
      if(button_dec_previous == false && button_dec_pressed == true && debounceExpired(lastChangeDec, 200)){
          updateModeSwitchButtons(BUTTON_DEC);
          Serial.println("Button DEC pressed");
          lastChangeDec = millis();
      }
      else if(button_inc_previous == false && button_inc_pressed == true && debounceExpired(lastChangeInc, 200)){
          updateModeSwitchButtons(BUTTON_INC);
          Serial.println("Button INC pressed");
          lastChangeInc = millis();
      }

  }

  // Always update previous states at the end
  button_dec_previous = button_dec_pressed;
  button_inc_previous = button_inc_pressed;   
  accelerometer.read_if_available(); // Read accelerometer data if available
  updateModeSwitchAccelerometer(accelerometer.getOrientation()); // Update the mode switch based on orientation

  if(!button_dec_pressed && !button_inc_pressed) // Only switch modes if no buttons are pressed
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (currentMode())
    {
        case TEMP:
          envSensors.read_temperature_dht11();
          envSensors.read_temperature_linear_temp_sensor();
          envSensors.read_temperature_analog_temp_sensor();
          // First line: D:<val> L:<val>
          lcd.print("D:");
          lcd.print(envSensors.get_temperature_dht11(), 1);
          lcd.print(" L:");
          lcd.print(envSensors.get_temperature_linear_temp_sensor(), 1);
          // Second line: A:<val> Avg:<val>
          lcd.setCursor(0, 1);
          lcd.print("A:");
          lcd.print(envSensors.get_temperature_analog_temp_sensor(), 1);
          lcd.print(" Avg:");
          lcd.print(envSensors.get_average_temperature(), 1);
          break;
        case HUMIDITY:
          envSensors.read_humidity();
          lcd.print("Humidity:");
          lcd.setCursor(0, 1);
          lcd.print(envSensors.get_humidity(), 1);
          lcd.print(" %");
          break;
        case LIGHT:
          envSensors.read_light();
          lcd.print("Light:");
          lcd.setCursor(0, 1);
          lcd.print(envSensors.get_light());
          break;
        case GAS:
          envSensors.read_gas();
          lcd.print("Gas:");
          lcd.setCursor(0, 1);
          lcd.print(envSensors.get_gas());
          break;
        case NEUTRAL:
          lcd.print("Welcome to my");
          lcd.setCursor(0, 1);
          lcd.print("Env Sensor Hub!");
          break;
    }

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