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
FadeLED_Lin::FadeLED_Lin(
    Adafruit_TLC59711& device, 
    uint16_t channel,
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
FadeLED_Lin::FadeLED_Lin(
    Adafruit_TLC5947& device, 
    uint16_t channel,
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
        byte val;   // will hold current output value
        unsigned long d = millis() - m_switchTime;  // time since state change
        if (m_state == eTurningOn) {
            // Has fade time completed?
            if ((long) (d - m_onTime) >= 0) {
                // If so, output will be fully on.
                m_state = eOn;
                val = 255;
            } else {
                // Otherwise, interpolate output.
                val = (byte) ((d * 255) / m_onTime);
            }
            // Set output value, inverting if necessary.
            setPWM(m_invert ? (255 - val) : val);
        //     analogWrite(m_pin, m_invert ? (255 - val) : val);
        } else if (m_state == eTurningOff) {
            // Has fade time completed?
            if ((long) (d - m_offTime) >= 0) {
                // If so, output will be fully off.
                m_state = eOff;
                val = 0;
            } else {
                // Otherwise, interpolate output.
                val = (byte) (255 - ((d * 255) / m_offTime));
            }
            // Set output value, inverting if necessary.
            setPWM(m_invert ? (255 - val) : val);
        //     analogWrite(m_pin, m_invert ? (255 - val) : val);
        }
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}
