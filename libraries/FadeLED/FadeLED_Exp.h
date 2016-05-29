#ifndef _FADE_LED_EXP__H_
#define _FADE_LED_EXP__H_

#include <FadeLED.h>

/**
 * FadeLED_Lin
 *
 * This class extends FadeLED to implement an exponential fade between full-off
 * and full-on on a PWM GPIO pin.  The fade times for turning on and off are
 * individually settable.  The output can also be inverted for an active-low
 * connection, that is, fully on is 0 volts and fully off is Vcc (5v on Arduino
 * Uno).  This setting would be used if current through an LED is being sinked
 * from Vcc, rather than sourced into ground.
 *
 * Note that the fade algorithm calculates the exponential fade curve from
 * the on and off times; however, because integer output levels are retained
 * between updates, truncation occurs which causes the actual fade times to be
 * slightly shorter than those passed to the constructor.
 *
 * This class inherits methods read and write from FadeLED.
 */

class FadeLED_Exp : public FadeLED
{
    private:
        double m_onTau;     // turn-on decay constant
        double m_offTau;    // turn-off decay constant
        byte m_output;      // current output level
        
    public:
        /**
         * Constructor
         *
         * @param pin PWM pin (analog write) to be controlled
         * @param onTime turn-on time (milliseconds)
         * @param offTime turn-off time (milliseconds)
         * @param invert true if output must go low to turn on connected LED,
         *               false otherwise [optional, default false]
         */
        FadeLED_Exp(
            const byte pin, 
            const unsigned int onTime, 
            const unsigned int offTime,
            const bool invert = false
        );
        
        /**
         * Update this object's state.
         *
         * @return true if object's state was updated
         */
        virtual bool update();
};

#endif
