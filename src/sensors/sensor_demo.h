#ifndef SENSOR_DEMO_H
#define SENSOR_DEMO_H

#include "sensors.h"

// Function to demonstrate polymorphic sensor usage
void demonstratePolymorphism();

// Function to read all sensors using polymorphic interface
void readAllSensorsPolymorphically(sensors& envSensors);

#endif