#ifndef _FADE_LED_FUNC__H_
#define _FADE_LED_FUNC__H_

#include <FadeLED.h>

/**
 * FadeLED_Func
 *
 * This class extends FadeLED to implement a fade between full-off and
 * full-on on a PWM output.  The fade times for turning on and off are
 * individually settable.  If the PWM output is a pin on the Arduino processor,
 * it can also be inverted for an active-low connection, that is, fully on is
 * 0 volts and fully off is Vcc (5v on Arduino UNO, for example).  This setting
 * would be used if current through an LED is being sinked from Vcc, rather than
 * sourced into ground.
 * 
 * This class does not specify a fade curve, unlike the _Lin and _Exp subclasses
 * of the FadeLED class.  Instead, each time a FadeLED_Func updates, it computes
 * the relative output value scaled between 0.0 (full off) and 1.0 (full on).
 * The calling code can get the current output value by calling get(), computing
 * a new value in the range of [0.0, 1.0], and passing that back to the set()
 * method which will convert it to an integer value which will be written to the
 * PWM output specified by the constructor.
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
         * Constructor to drive Arduino PWM output pin
         *
         * @param pin PWM pin (analog write) to be controlled
         * @param onTime turn-on time (milliseconds)
         * @param offTime turn-off time (milliseconds)
         * @param invert true if output must go low to turn on connected LED,
         *               false otherwise [optional, default false]
         */
        FadeLED_Func(
            const byte pin, 
            const unsigned long onTime, 
            const unsigned long offTime,
            const bool invert = false
        );
        
// #if defined(ALLOW_12CH)
        /**
         * Constructor to drive Adafruit 12-Channel 16-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC59711 device
         * @param channel Channel, in range 0 to 11
         * @param onTime turn-on time (milliseconds)
         * @param offTime turn-off time (milliseconds)
         */
        FadeLED_Func(
            Adafruit_TLC59711* device, 
            const uint16_t channel,
            const unsigned long onTime, 
            const unsigned long offTime
        );
// #endif

// #if defined(ALLOW_24CH)
        /**
         * Constructor to drive Adafruit 24-Channel 12-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC5947 device
         * @param channel Channel, in range 0 to 23
         * @param onTime turn-on time (milliseconds)
         * @param offTime turn-off time (milliseconds)
         */
        FadeLED_Func(
            Adafruit_TLC5947* device,
            const uint16_t channel,
            const unsigned long onTime, 
            const unsigned long offTime
        );
// #endif

        /**
         * Update this object's state.
         *
         * @return true if object's state was updated
         */
        virtual bool update();

        /**
         * Get fraction of time passed between start and stop times of
         * ramp-up or ramp-down of fade.
         * 
         * @return Fraction of ramp interval, between 0.0 and 1.0
         */
        double get() const;

        /**
         * Set output level
         * 
         * @param f output level between 0.0 (fully off) and 1.0 (fully on)
         */
        void set(const double f);
};

#endif
