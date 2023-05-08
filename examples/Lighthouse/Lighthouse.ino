#include <FadeLED_Func.h>
#include <Pulser.h>

// This example code drives an LED simulating a lighthouse.
//
// Dependencies:
//    https://github.com/twrackers/FadeLED-library
//    https://github.com/twrackers/Pulser-library
//    https://github.com/twrackers/StateMachine-library

Pulser pulser(1200, 3800);

FadeLED_Func fader(LED_BUILTIN, 600, 600);

void setup()
{
  // No further setup required.
}

void loop()
{
  // Update the fader object for the current time.
  fader.update();
  // Set the desired output value.
  double f = fader.get();
  fader.set(pow(f, 4.0));
  // If it's time to update the pulser object, do so.
  if (pulser.update()) {
    fader.write(pulser.read());
  }
}
