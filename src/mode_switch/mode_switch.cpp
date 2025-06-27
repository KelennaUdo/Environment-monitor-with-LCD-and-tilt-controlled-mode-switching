#include "mode_switch.h"
#include <SparkFun_MMA8452Q.h>   // Accelerometer library

// ----- Accelerometer instance (extern or create your own) -----
// extern MMA8452Q accel;           // Declared in main.cpp

// ----- FSM states -----
enum TiltFSMState : uint8_t
{
    WAITING_FOR_TILT = 0,
    AWAITING_RETURN_TO_NEUTRAL
};

// ----- File-local (static) variables -----
static Mode          _mode  = NEUTRAL;
static TiltFSMState  _fsm   = WAITING_FOR_TILT;
static uint32_t      _debounceMs = 250;   // debounce / settle time
static uint32_t      _lastChange = 0;
static byte          _selectedOrientation = LOCKOUT;
static byte          _lastOrientation = LOCKOUT;

/* -------------------------------------------------- */
void modeSwitchBegin()
{
    _mode  = NEUTRAL;
    _fsm   = WAITING_FOR_TILT;
    _lastChange = millis();
}

/* -------------------------------------------------- */
static bool debounceExpired()
{
    return (millis() - _lastChange) > _debounceMs;
}

/* -------------------------------------------------- */
static Mode orientationToMode(byte orientation)
{
    switch (orientation)
    {
        case PORTRAIT_U:   return TEMP;
        case PORTRAIT_D:   return HUMIDITY;
        case LANDSCAPE_R:  return LIGHT;
        case LANDSCAPE_L:  return GAS;
        default:           return NEUTRAL;   // LOCKOUT or unknown
    }
}

/* -------------------------------------------------- */
void updateModeSwitch(byte orientation)
{

    // ----- Finite-state machine -----
    switch (_fsm)
    {
        case WAITING_FOR_TILT:
            if ((orientation != LOCKOUT) && (debounceExpired()) && (orientation != _lastOrientation))
            {
                _selectedOrientation = orientation;
                _fsm = AWAITING_RETURN_TO_NEUTRAL;
                _lastChange = millis();
            }
            break;

        case AWAITING_RETURN_TO_NEUTRAL:
            if (orientation == LOCKOUT && debounceExpired())
            {
                _mode = orientationToMode(_selectedOrientation);
                _fsm  = WAITING_FOR_TILT;
                _lastChange = millis();

                // Optional: debug feedback
                Serial.print(F("Mode switched to: "));
                Serial.println(_mode);
            }
            break;
    }
  _lastOrientation = orientation;
}

/* -------------------------------------------------- */
Mode currentMode()
{
    return _mode;
}
