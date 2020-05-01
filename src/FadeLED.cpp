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
    m_switchTime(0),
    m_pin(pin),
    m_invert(invert)
{
    pinMode(m_pin, OUTPUT);
    analogWrite(m_pin, m_invert ? 255 : 0);
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
