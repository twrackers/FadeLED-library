#include <FadeLED_Lin.h>

// Constructor
//
// This is a subclass of FadeLED, implementing linear fade curves.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED_Lin::FadeLED_Lin(
    const byte pin, 
    const unsigned long onTime, 
    const unsigned long offTime,
    const bool invert
) : FadeLED(pin, invert), 
    m_onTime(onTime), 
    m_offTime(offTime)
{
}

#if defined(ALLOW_12CH)
// Constructor
//
// This is a subclass of FadeLED, implementing linear fade curves.
// The channel selects an output on a 12-channel PWM driver.  Because
// the driver device supports daisy-chaining, the channel is not limited
// to the range of 0 through 11.
FadeLED_Lin::FadeLED_Lin(
    Adafruit_TLC59711* device, 
    const uint16_t channel,
    const unsigned long onTime, 
    const unsigned long offTime
) : FadeLED(device, channel), 
    m_onTime(onTime), 
    m_offTime(offTime)
{
}
#endif

#if defined(ALLOW_24CH)
// Constructor
//
// This is a subclass of FadeLED, implementing linear fade curves.
// The channel selects an output on a 24-channel PWM driver.  Because
// the driver device supports daisy-chaining, the channel is not limited
// to the range of 0 through 23.
FadeLED_Lin::FadeLED_Lin(
    Adafruit_TLC5947* device, 
    const uint16_t channel,
    const unsigned long onTime, 
    const unsigned long offTime
) : FadeLED(device, channel), 
    m_onTime(onTime), 
    m_offTime(offTime)
{
}
#endif

// Performs the update cycle.
bool FadeLED_Lin::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        uint16_t val;   // will hold current output value
        if (m_state == eOff) {
            val = 0;
        } else if (m_state == eOn) {
            val = m_scale;
        } else if (m_state == eTurningOn) {
            unsigned long d = millis() - m_switchTime;  // time since state change
            // Has fade time completed?
            if ((long) (d - m_onTime) >= 0L) {
                // If so, output will be fully on.
                m_state = eOn;
                val = m_scale;
            } else {
                // Otherwise, interpolate output.
                val = (uint16_t) ((d * m_scale) / m_onTime);
            }
            // Set output value, inverting if necessary.
            setPWM(m_invert ? (m_scale - val) : val);
        } else if (m_state == eTurningOff) {
            unsigned long d = millis() - m_switchTime;  // time since state change
            // Has fade time completed?
            if ((long) (d - m_offTime) >= 0) {
                // If so, output will be fully off.
                m_state = eOff;
                val = 0;
            } else {
                // Otherwise, interpolate output.
                val = (uint16_t) (m_scale - ((d * m_scale) / m_offTime));
            }
            // Set output value, inverting if necessary.
            setPWM(m_invert ? (m_scale - val) : val);
        }
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}
