#ifndef MODE_SWITCH_H
#define MODE_SWITCH_H

#include <Arduino.h>

// ----- Public enumeration of operating modes -----
enum Mode : uint8_t
{
    NEUTRAL = 0,
    TEMP,
    HUMIDITY,
    LIGHT,
    GAS
};

// ------------ API -------------
/**
 * @brief  Initialise the mode-switch (call once in setup after accel.init()).
 */
void modeSwitchBegin();

/**
 * @brief  Poll the accelerometer, update the internal FSM and
 *         change mode if the user completed a tilt-and-return gesture.
 *         Call this once every loop iteration (non-blocking).
 */
void updateModeSwitch(byte orientation);

/**
 * @return The currently active operating mode.
 */
Mode currentMode();

#endif // MODE_SWITCH_H
