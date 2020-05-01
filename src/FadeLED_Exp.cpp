#include <FadeLED_Exp.h>

// Constructor
//
// This is a subclass of FadeLED, implementing exponential fade curves.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED_Exp::FadeLED_Exp(
    const byte pin, 
    const unsigned int onTime, 
    const unsigned int offTime,
    const bool invert
) : FadeLED(pin, invert), m_output(0)
{
    double dt;
    // Calculate turning-on decay constant.
    dt = (double) onTime / (double) m_updateDelta;
    m_onTau = pow((double) 255, -1.0 / dt);
    // Calculate turning-off decay constant.
    dt = (double) offTime / (double) m_updateDelta;
    m_offTau = pow((double) 255, -1.0 / dt);
}

// Performs the update cycle.
bool FadeLED_Exp::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        unsigned long d = millis() - m_switchTime;  // time since state change
        if (m_state == eTurningOn) {
            // Update output based on current output and decay constant.
            m_output = 255 - (255 - m_output) * m_onTau;
            // If fully-on is reached, change state to on.
            if (m_output == 255) {
                m_state = eOn;
            }
        } else if (m_state == eTurningOff) {
            // Update output based on current output and decay constant.
            m_output *= m_offTau;
            // If fully-off is reached, change state to off.
            if (m_output == 0) {
                m_state = eOff;
            }
        }
        // Write new output value, inverting if necessary.
        analogWrite(
            m_pin,
            m_invert ? (255 - m_output) : m_output
        );
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}
