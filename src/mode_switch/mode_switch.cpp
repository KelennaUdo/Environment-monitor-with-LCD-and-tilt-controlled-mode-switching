#include "mode_switch.h"
#include <SparkFun_MMA8452Q.h>   // Accelerometer library


// ----- Accelerometer instance (extern or create your own) -----
// extern MMA8452Q accel;           // Declared in main.cpp




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
        case LANDSCAPE_R:  return NEUTRAL;
        case LANDSCAPE_L:  return GAS;
        default:           return LIGHT;   // LOCKOUT or unknown
    }
}

/* -------------------------------------------------- */
void updateModeSwitchAccelerometer(byte orientation)
{

    // ----- Finite-state machine -----
    switch (_fsm)
    {
        case WAITING_FOR_TILT:
            if ((orientation != LANDSCAPE_R) && (debounceExpired()) && (orientation != _lastOrientation))
            {
                _selectedOrientation = orientation;
                _fsm = AWAITING_RETURN_TO_NEUTRAL;
                _lastChange = millis();
            }
            break;

        case AWAITING_RETURN_TO_NEUTRAL:
            if (orientation == LANDSCAPE_R && debounceExpired())
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

void updateModeSwitchButtons(uint8_t button_pressed)
{
    if (debounceExpired())
    {
        _lastChange = millis();
        switch (button_pressed)
        {
                case BUTTON_INC:
                if (_mode < GAS) {
                    _mode = static_cast<Mode>(_mode + 1);
                } else {
                    _mode = TEMP; // wrap around
                }
                break;
            case BUTTON_DEC:
                if (_mode > NEUTRAL) {
                    _mode = static_cast<Mode>(_mode - 1);
                } else {
                    _mode = GAS; // wrap around
                }
                break;
        }
        Serial.print(F("Mode switched to: "));
        Serial.println(_mode);
    }
}

/* -------------------------------------------------- */
Mode currentMode()
{
    return _mode;
}
