#include <Pulser.h>
#include <FadeLED_Exp.h>

// This example code drives 3 LEDs simulating incandescent bulbs,
// which often have turn-on and turn-off times.
//
// Dependencies:
//    https://github.com/twrackers/StateMachine-library
//    https://github.com/twrackers/Pulser-library
//    https://github.com/twrackers/FadeLED-library

// Define class Lightbulb as a subclass of Pulser.
// In Object-Oriented-Programming speak, a Lightbulb "isa" Pulser,
// with the added attribute of a FadeLED_Exp object to actually
// handle the ramp-up and ramp-down of a PWM output, presumably
// with an LED attached to it.  The on/off timing information
// is handled by the parent Pulser object.
class Lightbulb : public Pulser
{
  private:
    FadeLED_Exp* m_lightbulb;   // pointer to FadeLED_Exp object

  public:
    // Constructor
    Lightbulb(int pin, int on, int off, int fadeOn, int fadeOff) : 
      Pulser(on, off),
      m_lightbulb(new FadeLED_Exp(pin, fadeOn, fadeOff))
    {
      m_lightbulb->write(Pulser::read());
    }

    // Destructor
    virtual ~Lightbulb()
    {
      delete m_lightbulb;
    }

    // Perform update on this Lightbulb.
    bool update()
    {
      // Update the contained FadeLED_Exp object on every pass.
      // It will decide for itself if any action must be taken.
      m_lightbulb->update();
      
      // Time to update this object's state?
      if (Pulser::update()) {
        
        // If so, change LED's state based on Pulser's state.
        m_lightbulb->write(Pulser::read());
        // We have updated this object.
        return true;
        
      }
      // Nope, no update this time around.
      return false;
    }
};

// Define three Lightbulb objects on 3 GPIO pins with different fade times.
// Note: the 3 GPIO pins selected are all PWM-capable on Arduino Uno and
// Arduino Mega.
const int on_time = 500;
const int off_time = 1000;
Lightbulb s1(11, on_time, off_time, 10, 10);    // very fast
Lightbulb s2(10, on_time, off_time, 200, 200);  // moderately fast
Lightbulb s3(9, on_time, off_time, 400, 400);   // slow

// Create an array of pointer-to-Lightbulb objects for the
// StateMachine::updateAll method.
int numLightbulbs = 3;
StateMachine* Lightbulbs[] = { &s1, &s2, &s3 };

void setup()
{
  // No further setup required.
}

void loop()
{
  // Update all the Lightbulb objects.
  StateMachine::updateAll(Lightbulbs, numLightbulbs);
}
