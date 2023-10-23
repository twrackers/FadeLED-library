#ifndef _FADE_LED__H_
#define _FADE_LED__H_

#if defined(ALLOW_12CH)
#pragma message("ALLOW_12CH")
#include <Adafruit_TLC59711.h>
#endif
#if defined(ALLOW_24CH)
#pragma message("ALLOW_24CH")
#include <Adafruit_TLC5947.h>
#endif

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
#if defined(ALLOW_12CH)
        Adafruit_TLC59711* m_dev12; // pointer to 12-channel device
#endif
#if defined(ALLOW_24CH)
        Adafruit_TLC5947* m_dev24;  // pointer to 24-channel device
#endif
        const uint16_t m_pin;       // pin or channel to drive
        const uint16_t m_scale;     // full-scale value
        const bool m_invert;        // true if output is active-low
        
    public:
        /**
         * Constructor to drive Arduino PWM output pin
         *
         * @param pin PWM pin (analog write) to be controlled
         * @param invert true if output must go low to turn on connected LED,
         *               false otherwise [default false]
         */
        FadeLED(const byte pin, const bool invert = false);

#if defined(ALLOW_12CH)
        /**
         * Constructor to drive Adafruit 12-Channel 16-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC59711 device
         * @param channel Channel, in range 0 to 11
         */
        FadeLED(Adafruit_TLC59711& device, uint16_t channel);
#endif

#if defined(ALLOW_24CH)
        /**
         * Constructor to drive Adafruit 24-Channel 12-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC5947 device
         * @param channel Channel, in range 0 to 23
         */
        FadeLED(Adafruit_TLC5947& device, uint16_t channel);
#endif

        /**
         * Set PWM channel/pin output
         * 
         * This method uses members m_dev12 and m_dev24 to determine
         * what type of PWM pin is being set.  If both members are
         * NULL, then m_pin is assumed to be a PWM-capable pin on
         * the processor.
         * The accepted data size depends on the device being set.
         * Out-of-range values will have high bits truncated.
         * 
         * TLC59711: 16 bits
         * TLC5947:  12 bits
         * PWM:      8 bits
         * 
         * @param pwm Value to which pin is set, 16-bit unsigned value
         */
        void setPWM(const uint16_t pwm);

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
