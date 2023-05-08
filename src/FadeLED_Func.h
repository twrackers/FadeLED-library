#ifndef _FADE_LED_Func__H_
#define _FADE_LED_Func__H_

#include <FadeLED.h>

/**
 * FadeLED_Func
 *
 * This class extends FadeLED to implement a fade between full-off and
 * full-on on a PWM GPIO pin.  The fade times for turning on and off are
 * individually settable.  The output can also be inverted for an active-low
 * connection, that is, fully on is 0 volts and fully off is Vcc (5v on Arduino
 * Uno).  This setting would be used if current through an LED is being sinked
 * from Vcc, rather than sourced into ground.
 * 
 * This class does not specify a fade curve, unlike the _Lin and _Exp variants
 * of the FadeLED class.  Instead, each time a FadeLED_Func updates, it computes
 * the relative output value scaled between 0.0 (full off) and 1.0 (full on).
 * The calling code can get the current output value by calling get(), computing
 * a new value in the range of [0.0, 1.0], and passing that back to the set()
 * method which will convert it to a byte value which will be written to the
 * analog output specified by the constructor.
 *
 * This class inherits methods read() and write() from FadeLED.
 */

class FadeLED_Func : public FadeLED
{
    private:
        const unsigned long m_onTime;   // turn-on time (msec)
        const unsigned long m_offTime;  // turn-off time (msec)
        double m_current;               // current value in range [0.0, 1.0]
        
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
        FadeLED_Func(
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

        double get() const;

        void set(const double f);
};

#endif