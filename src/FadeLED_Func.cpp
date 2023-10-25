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

#if defined(ALLOW_12CH)
// Constructor
//
// This is a subclass of FadeLED, implementing fade curves.
// The channel selects an output on a 12-channel PWM driver.  Because
// the driver device supports daisy-chaining, the channel is not limited
// to the range of 0 through 11.
FadeLED_Func::FadeLED_Func(
    const Adafruit_TLC59711& device, 
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
// This is a subclass of FadeLED, implementing fade curves.
// The channel selects an output on a 24-channel PWM driver.  Because
// the driver device supports daisy-chaining, the channel is not limited
// to the range of 0 through 23.
FadeLED_Func::FadeLED_Func(
    const Adafruit_TLC5947& device, 
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
bool FadeLED_Func::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        if (m_state == eOff) {
            m_current = 0.0;
        } else if (m_state == eOn) {
            m_current = 1.0;
        } else if (m_state == eTurningOn) {
            unsigned long d = millis() - m_switchTime;  // time since state change
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
            unsigned long d = millis() - m_switchTime;  // time since state change
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

// Get the fraction of ramp interval which has passed so far.
double FadeLED_Func::get() const
{
    return m_current;
}

// Set the output channel.
//
// If f == 0.0, output will be set to fully off.
// If f == 1.0, output will be set to fully on.
// For any other value, output will be interpolated between off and on.
//
// On Arduino PWM pins, set() will update the output pin immediately.
// On PWM driver devices, set() will only take effect the next time
// a write() is called on the device itself.
void FadeLED_Func::set(const double f)
{
    uint16_t val = (uint16_t) (constrain(f, 0.0, 1.0) * (double) m_scale);
    // Set output value, inverting if necessary.
    setPWM(m_invert ? (m_scale - val) : val);
}
