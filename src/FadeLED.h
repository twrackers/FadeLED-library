#ifndef _FADE_LED__H_
#define _FADE_LED__H_

#include <StateMachine.h>

/**
 * FadeLED - base class for FadeLED_Lin and FadeLED_Exp
 *
 * This base class handles the state and transitions of a state machine which
 * can control a PWM-capable GPIO pin, usually driving an LED.  The "analog
 * output" transitions slowly between the fully on and off states.  The derived
 * classes FadeLED_Lin and FadeLED_Exp produce the desired output-vs-time curves
 * of the transitions between on and off.
 */
class FadeLED : public StateMachine
{
    protected:
        enum E_STATE {
            eOff, eTurningOn, eOn, eTurningOff
        } m_state;                  // state machine current state
        
        unsigned long m_switchTime; // time when on/off state changed
        const byte    m_pin;        // GPIO pin to drive
        const bool    m_invert;     // true if output is active-low
        
    public:
        /**
         * Constructor
         *
         * @param pin PWM pin (analog write) to be controlled
         * @param invert true if output must go low to turn on connected LED,
         *               false otherwise [default false]
         */
        FadeLED(const byte pin, const bool invert = false);

        /**
         * Check if output is fully off
         * 
         * @return true if output state is off, false otherwise
         */
        bool isOff() const;
        
        /**
         * Get the current state
         *
         * @return true if output is on or turning on, false otherwise
         */
        bool read() const;
        
        /**
         * Set the desired state
         *
         * @param state true to change object state to turning-on,
         *              false to change state to turning-off
         */
        void write(bool state);
        
        /**
         * Update this object's state
         *
         * @return true if object's state was updated
         */
        virtual bool update();
};

#endif
