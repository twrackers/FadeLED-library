#include <FadeLED.h>

// Constructor
//
// An instance of this class runs on a 10 msec (100 Hz) update interval.
// This constructor will be called by the constructors of subclasses of FadeLED,
// two of which are FadeLED_Lin and FadeLED_Exp.
// The GPIO pin specified when calling this constructor must be one which
// supports PWM (pulse-width modulation) output via the Arduino analogWrite()
// function.
FadeLED::FadeLED(const byte pin, const bool invert) : 
    StateMachine(10, true),
    m_state(eOff),
    m_switchTime(0L),
#if defined(ALLOW_12CH)
    m_dev12(NULL),
#endif
#if defined(ALLOW_24CH)
    m_dev24(NULL),
#endif
    m_pin((uint16_t) pin),
    m_invert(invert)
{
    pinMode(m_pin, OUTPUT);
    analogWrite(m_pin, m_invert ? 255 : 0);
}

#if defined(ALLOW_12CH)
// Constructor
//
// An instance of this class runs on a 10 msec (100 Hz) update interval.
// This constructor will be called by the constructors of subclasses of FadeLED,
// two of which are FadeLED_Lin and FadeLED_Exp.
// This constructor assigns the FadeLED object to one channel of an
// Adafruit TLC59711 12-channel PWM driver.
FadeLED::FadeLED(Adafruit_TLC59711& device, const uint16_t channel) : 
    StateMachine(10, true),
    m_state(eOff),
    m_switchTime(0L),
    m_dev12(&device),
#if defined(ALLOW_24CH)
    m_dev24(NULL),
#endif
    m_pin(channel),
    m_invert(false)
{
    m_dev12->setPWM(m_pin, 0);
    m_dev12->write();
}
#endif

#if defined(ALLOW_24CH)
// Constructor
//
// An instance of this class runs on a 10 msec (100 Hz) update interval.
// This constructor will be called by the constructors of subclasses of FadeLED,
// two of which are FadeLED_Lin and FadeLED_Exp.
// This constructor assigns the FadeLED object to one channel of an
// Adafruit TLC5947 24-channel PWM driver.
FadeLED::FadeLED(Adafruit_TLC5947& device, uint16_t channel) : 
    StateMachine(10, true),
    m_state(eOff),
    m_switchTime(0L),
#if defined(ALLOW_12CH)
    m_dev12(NULL),
#endif
    m_dev24(&device),
    m_pin(channel),
    m_invert(false)
{
    m_dev24->setPWM(m_pin, 0);
    m_dev24->write();
}
#endif

// Write value to PWM channel or pin.
//
// Notes:
// (1) 16-bit parameter values are truncated to match the device.
// (2) Writes to processor PWM pins take effect immediately.
//     Writes to TLC devices require a write() call to the
//     device to have all prior setPWM() calls take effect.
void FadeLED::setPWM(const uint16_t pwm) {
#if defined(ALLOW_12CH)
    if (m_dev12) {
        // 16-bit PWM channels
        m_dev12->setPWM(m_pin, pwm);
        return;
    }
#endif
#if defined(ALLOW_24CH)
    if (m_dev24) {
        // 12-bit PWM channels
        m_dev24->setPWM(m_pin, pwm & 0x0FFF);
        return;
    }
#endif
    analogWrite(m_pin, pwm & 0x00FF);
}

// Check if current state is fully off (dark).
//
// Checks if state is off, meaning the LED is fully dark.  Useful to
// determine if a slow pulse has completed.
bool FadeLED::isOff() const {
    return (m_state == eOff);
}

// Gets the current state of the object.
//
// Turning-on and turning-off are treated as the same as on and off states
// respectively.  So this method returns the most recently commanded state,
// even if that state (fully on or fully off) hasn't been reached yet.
bool FadeLED::read() const
{
    return (m_state == eTurningOn) || (m_state == eOn);
}

// Commands the object to a specified state, on or off.
//
// If the specified state is already the commanded state, no action is taken.
// For example, if the FadeLED object is still turning off when an off state
// is commanded (again), there will be no affect on the object, including on
// the fade already underway.
void FadeLED::write(bool state)
{
    // Is the on state requested?
    if (state) {
        // If on requested, only act if it's now off or turning off.
        if (m_state == eOff || m_state == eTurningOff) {
            m_state = eTurningOn;
            m_switchTime = millis();    // note switch time
        }
    } else {
        // If off requested, only act if it's now on or turning on.
        if (m_state == eOn || m_state == eTurningOn) {
            m_state = eTurningOff;
            m_switchTime = millis();    // note switch time
        }
    }
}

// Performs the update cycle.
bool FadeLED::update()
{
    return StateMachine::update();
}
