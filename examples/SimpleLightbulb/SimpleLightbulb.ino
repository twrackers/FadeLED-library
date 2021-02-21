#include <Pulser.h>
#include <FadeLED_Exp.h>

// This example code drives an LED simulating an incandescent bulb.
//
// Dependencies:
//    https://github.com/twrackers/StateMachine-library
//    https://github.com/twrackers/Pulser-library
//    https://github.com/twrackers/FadeLED-library

Pulser pulser(500, 1000);

FadeLED_Exp fader(9, 400, 400);

void setup()
{
  // No further setup required.
}

void loop()
{
  fader.update();
  if (pulser.update()) {
    fader.write(pulser.read());
  }
}
