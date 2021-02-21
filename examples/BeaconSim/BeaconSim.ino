#include <Pulser.h>
#include <FadeLED_Lin.h>

// This example code drives 3 LEDs as "beacons", which I'm
// defining as slowly flashing lights which ramp up and down
// between off and fully on.
//
// Dependencies:
//    https://github.com/twrackers/StateMachine-library
//    https://github.com/twrackers/Pulser-library
//    https://github.com/twrackers/FadeLED-library

// Define class Beacon as a subclass of Pulser.
// In Object-Oriented-Programming speak, a Beacon "isa" Pulser,
// with the added attribute of a FadeLED_Lin object to actually
// handle the ramp-up and ramp-down of a PWM output, presumably
// with an LED attached to it.  The on/off timing information
// is handled by the parent Pulser object.
class Beacon : public Pulser
{
  private:
    FadeLED_Lin* m_beacon;   // pointer to FadeLED_Lin object

  public:
    // Constructor
    Beacon(int pin, int on, int off, int fadeOn, int fadeOff) : 
      Pulser(on, off),
      m_beacon(new FadeLED_Lin(pin, fadeOn, fadeOff))
    {
      m_beacon->write(Pulser::read());
    }

    // Destructor
    virtual ~Beacon()
    {
      delete m_beacon;
    }

    // Perform update on this Beacon.
    bool update()
    {
      // Update the contained FadeLED_Lin object on every pass.
      // It will decide for itself if any action must be taken.
      m_beacon->update();
      
      // Time to update this object's state?
      if (Pulser::update()) {
        
        // If so, change LED's state based on Pulser's state.
        m_beacon->write(Pulser::read());
        // We have updated this object.
        return true;
        
      }
      // Nope, no update this time around.
      return false;
    }
};

// Define three Beacon objects on 3 GPIO pins with slightly different timing.
// Note: the 3 GPIO pins selected are all PWM-capable on Arduino Uno and
// Arduino Mega.
Beacon s1(9, 1500, 5000, 1500, 1500);
Beacon s2(10, 1500, 5200, 1500, 1500);
Beacon s3(11, 1500, 5400, 1500, 1500);

// Create an array of pointer-to-Beacon objects for the
// StateMachine::updateAll method.
int numBeacons = 3;
StateMachine* beacons[] = { &s1, &s2, &s3 };

void setup()
{
  // No further setup required.
}

void loop()
{
  // Update all the beacon objects.
  StateMachine::updateAll(beacons, numBeacons);
}
