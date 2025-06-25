#include "accelerometer.h"

Accelerometer::Accelerometer() 
    : accelerometer_main(0x1D), // <-- Set the address here
      x{0}, y{0}, z{0}, 
      calculatedX{0.0f}, calculatedY{0.0f}, calculatedZ{0.0f}, 
      orientation{0} {
    // Constructor initializes the accelerometer instance
}

Accelerometer::~Accelerometer() {
    // Destructor can be used for cleanup if needed
    // Currently, no specific cleanup is required for the MMA8452Q instance
}

void Accelerometer::initialize(MMA8452Q_Scale fsr, MMA8452Q_ODR odr) {
    Serial.println("Attempting accelerometer init...");
    if (!accelerometer_main.init(fsr, odr)) {
        Serial.println("Accelerometer initialization failed!");
        while(1);
    } else {
        Serial.println("Accelerometer initialized successfully.");
    }
}

void Accelerometer::read_if_available()
{
    if (!accelerometer_main.available()) {
       Serial.println("No new accelerometer data available.");
       return;
    }
    accelerometer_main.read();
    /* One I²C burst just finished inside available().
       Shadow-copy the freshly-latched values: */
    x  = accelerometer_main.x;
    y  = accelerometer_main.y;
    z  = accelerometer_main.z;

    calculatedX = accelerometer_main.cx;
    calculatedY = accelerometer_main.cy;
    calculatedZ = accelerometer_main.cz;

    orientation = accelerometer_main.readPL();
}

void Accelerometer::print_binary_accelerations() const {
    Serial.print("Raw X: ");
    Serial.print(x, BIN);
    Serial.print(" | Raw Y: ");
    Serial.print(y, BIN);
    Serial.print(" | Raw Z: ");
    Serial.println(z, BIN);
}

void Accelerometer::print_calculated_accelerations() const {
    Serial.print("Calculated X: ");
    Serial.print(calculatedX, 0);
    Serial.print(" g | Calculated Y: ");
    Serial.print(calculatedY, 0);
    Serial.print(" g | Calculated Z: ");
    Serial.println(calculatedZ, 0);

    // Serial.print("Calculated X: ");
    // Serial.print(accelerometer_main.cx, 4);
    // Serial.print(" g | Calculated Y: ");
    // Serial.print(accelerometer_main.cy, 4);
    // Serial.print(" g | Calculated Z: ");
    // Serial.println(accelerometer_main.cz, 4);
}


void Accelerometer::print_orinetation() const {
    Serial.print("Orientation: ");
    switch (orientation) {
        case PORTRAIT_U:
            Serial.println("Portrait Up");
            break;
        case PORTRAIT_D:
            Serial.println("Portrait Down");
            break;
        case LANDSCAPE_R:
            Serial.println("Landscape Right");
            break;
        case LANDSCAPE_L:
            Serial.println("Landscape Left");
            break;
        case LOCKOUT:
            Serial.println("flat");
            break;
    }
}

void Accelerometer::print_all() const {
    print_binary_accelerations(); // Print raw accelerometer data in binary
    print_calculated_accelerations(); // Print calculated accelerations in g's
    print_orinetation(); // Print current orientation
}