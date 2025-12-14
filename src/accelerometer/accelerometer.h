#include <SparkFun_MMA8452Q.h>
// #include <ArduinoSTL.h>

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H 

class Accelerometer {
private:
    MMA8452Q accelerometer_main; // <-- Add this instead
    int16_t x, y, z;          // Variables to hold accelerometer data
    float calculatedX, calculatedY, calculatedZ; // Variables for calculated accelerations
    byte orientation; // Variable to hold orientation data
    
public:
// Constructor and Destructor
    Accelerometer();
    ~Accelerometer();

// initialization and setup methods
    void initialize(MMA8452Q_Scale fsr = SCALE_2G, MMA8452Q_ODR odr = ODR_800);


// read_if_available checks if new data is available and call the read_accelerations method
    void read_if_available();   

    void print_binary_accelerations() const;
    void print_calculated_accelerations() const;
    void print_orinetation() const;
    void print_all() const;
  

// Getters for accelerometer data
    int16_t getX() const{
        return x; // Return the raw x-axis data
    }
    int16_t getY() const {
        return y; // Return the raw y-axis data
    }
    int16_t getZ() const  {
        return z; // Return the raw z-axis data
    }

    float getCalculatedX() const {
        return calculatedX; // Return the calculated x-axis acceleration in g's
    }
    float getCalculatedY() const {
        return calculatedY; // Return the calculated y-axis acceleration in g's
    }
    float getCalculatedZ() const {
        return calculatedZ; // Return the calculated z-axis acceleration in g's
    }

    byte getOrientation() const {
        return orientation; // Return the current orientation
    }
};



#endif 