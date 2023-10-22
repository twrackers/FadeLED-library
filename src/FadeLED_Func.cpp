#include <FadeLED_Func.h>

// Constructor
//
// This is a subclass of FadeLED, implementing fade curves.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED_Func::FadeLED_Func(
    const byte pin, 
    const unsigned long onTime, 
    const unsigned long offTime,
    const bool invert
) : FadeLED(pin, invert), 
    m_onTime(onTime), 
    m_offTime(offTime)
{
}

// Performs the update cycle.
bool FadeLED_Func::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        unsigned long d = millis() - m_switchTime;  // time since state change
        if (m_state == eTurningOn) {
            // Has fade time completed?
            if ((long) (d - m_onTime) >= 0) {
                // If so, output will be fully on.
                m_state = eOn;
                m_current = 1.0;
            } else {
                // Otherwise, interpolate output.
                m_current = (double) d / (double) m_onTime;
            }
        } else if (m_state == eTurningOff) {
            // Has fade time completed?
            if ((long) (d - m_offTime) >= 0) {
                // If so, output will be fully off.
                m_state = eOff;
                m_current = 0.0;
            } else {
                // Otherwise, interpolate output.
                m_current = 1.0 - (double) d / (double) m_offTime;
            }
        }
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}

double FadeLED_Func::get() const
{
    return m_current;
}

void FadeLED_Func::set(const double f)
{
    byte val = (byte) (constrain(f, 0.0, 1.0) * 255.0);
    // Set output value, inverting if necessary.
    analogWrite(m_pin, m_invert ? (255 - val) : val);
}
