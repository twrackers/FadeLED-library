#include <FadeLED_Lin.h>

// Constructor
//
// This is a subclass of FadeLED, implementing linear fade curves.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED_Lin::FadeLED_Lin(
    const byte pin, 
    const unsigned int onTime, 
    const unsigned int offTime,
    const bool invert
) : FadeLED(pin, invert), 
    m_onTime(onTime), 
    m_offTime(offTime)
{
}

// Performs the update cycle.
bool FadeLED_Lin::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        byte val;   // will hold current output value
        unsigned long d = millis() - m_switchTime;  // time since state change
        if (m_state == eTurningOn) {
            // Has fade time completed?
            if (d >= m_onTime) {
                // If so, output will be fully on.
                m_state = eOn;
                val = 255;
            } else {
                // Otherwise, interpolate output.
                val = (byte) ((d * 255) / m_onTime);
            }
            // Set output value, inverting if necessary.
            analogWrite(m_pin, m_invert ? (255 - val) : val);
        } else if (m_state == eTurningOff) {
            // Has fade time completed?
            if (d >= m_offTime) {
                // If so, output will be fully off.
                m_state = eOff;
                val = 0;
            } else {
                // Otherwise, interpolate output.
                val = (byte) (255 - ((d * 255) / m_offTime));
            }
            // Set output value, inverting if necessary.
            analogWrite(m_pin, m_invert ? (255 - val) : val);
        }
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}