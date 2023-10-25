#ifndef _FADE_LED_EXP__H_
#define _FADE_LED_EXP__H_

#include <FadeLED.h>

/**
 * FadeLED_Exp
 *
 * This class extends FadeLED to implement an exponential fade between full-off
 * and full-on on a PWM output.  The fade times for turning on and off are
 * individually settable.  If the PWM output is a pin on the Arduino processor,
 * it can also be inverted for an active-low connection, that is, fully on is
 * 0 volts and fully off is Vcc (5v on Arduino UNO, for example).  This setting
 * would be used if current through an LED is being sinked from Vcc, rather than
 * sourced into ground.
 *
 * This class inherits methods read() and write() from FadeLED.
 */

class FadeLED_Exp : public FadeLED
{
    private:
        double m_onTau;     // turn-on decay constant
        double m_offTau;    // turn-off decay constant
        double m_level;     // current fade level
        uint16_t m_output;  // current output value

        /**
         * Initialization of timing parameters
         */
        void init(
            const unsigned long onTime,
            const unsigned long offTime
        );
        
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
        FadeLED_Exp(
            const byte pin, 
            const unsigned long onTime, 
            const unsigned long offTime,
            const bool invert = false
        );
        
#if defined(ALLOW_12CH)
        /**
         * Constructor to drive Adafruit 12-Channel 16-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC59711 device
         * @param channel Channel, in range 0 to 11
         */
        FadeLED_Exp(
            Adafruit_TLC59711* device, 
            const uint16_t channel,
            const unsigned long onTime, 
            const unsigned long offTime
        );
#endif

#if defined(ALLOW_24CH)
        /**
         * Constructor to drive Adafruit 24-Channel 12-bit PWM LED Driver
         * 
         * @param device Attached Adafruit_TLC5947 device
         * @param channel Channel, in range 0 to 23
         */
        FadeLED_Exp(
            Adafruit_TLC5947* device,
            const uint16_t channel,
            const unsigned long onTime, 
            const unsigned long offTime
        );
#endif
        
        /**
         * Update this object's state.
         *
         * @return true if object's state was updated
         */
        virtual bool update();
};

#endif
