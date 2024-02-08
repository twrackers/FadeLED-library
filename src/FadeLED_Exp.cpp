#include <math.h>

#include <FadeLED_Exp.h>

// Private timing initialization code
//
// This is used by the constructors.
void FadeLED_Exp::init(
    const unsigned long onTime, 
    const unsigned long offTime
) {
    double scale = (double) m_scale;
    double delta = (double) m_updateDelta;
    // Calculate turning-on decay constant.
    m_onTau = 1.0 / pow(scale, delta / (double) onTime);
    // Calculate turning-off decay constant.
    m_offTau = 1.0 / pow(scale, delta / (double) offTime);
}

// Constructor
//
// This is a subclass of FadeLED, implementing exponential fade curves.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED_Exp::FadeLED_Exp(
    const byte pin, 
    const unsigned long onTime, 
    const unsigned long offTime,
    const bool invert
) : FadeLED(pin, invert), m_level(0.0), m_output(0)
{
    init(onTime, offTime);
}

#if defined(ALLOW_12CH)
// Constructor
//
// This is a subclass of FadeLED, implementing exponential fade curves.
// The PWM output is one of the channels of an Adafruit TLC59711 12-channel
// PWM driver.
FadeLED_Exp::FadeLED_Exp(
    Adafruit_TLC59711* device,
    const uint16_t channel,
    const unsigned long onTime, 
    const unsigned long offTime
) : FadeLED(device, channel), m_level(0.0), m_output(0)
{
    init(onTime, offTime);
}
#endif

#if defined(ALLOW_24CH)
// Constructor
//
// This is a subclass of FadeLED, implementing exponential fade curves.
// The PWM output is one of the channels of an Adafruit TLC5947 24-channel
// PWM driver.
FadeLED_Exp::FadeLED_Exp(
    Adafruit_TLC5947* device,
    const uint16_t channel,
    const unsigned long onTime, 
    const unsigned long offTime
) : FadeLED(device, channel), m_level(0.0), m_output(0)
{
    init(onTime, offTime);
}
#endif

// Performs the update cycle.
bool FadeLED_Exp::update()
{
    // Is it time to update this object?
    if (FadeLED::update()) {
        if (m_state == eOff) {
            m_output = 0;
        } else if (m_state == eOn) {
            m_output = m_scale;
        } else if (m_state == eTurningOn) {
            unsigned long d = millis() - m_switchTime;  // time since state change
            // Update output based on current output and decay constant.
            double scale = (double) m_scale;
            m_level = scale - (scale - m_level) * m_onTau;
            int output = int(round(m_level));
            // If fully-on is reached, change state to on.
            if (output >= m_scale) {
                m_output = m_scale;
                m_state = eOn;
            } else {
                m_output = (uint16_t) output;
            }
        } else if (m_state == eTurningOff) {
            unsigned long d = millis() - m_switchTime;  // time since state change
            // Update output based on current output and decay constant.
            m_level *= m_offTau;
            int output = int(round(m_level));
            // If fully-off is reached, change state to off.
            if (output <= 0) {
                m_output = 0;
                m_state = eOff;
            } else {
                m_output = (uint16_t) output;
            }
        }
        // Write new output value, inverting if necessary.
        setPWM(m_invert ? (m_scale - m_output) : m_output);
        // Object was updated.
        return true;
    }
    // Wasn't time to update.
    return false;
}
