#include <Arduino.h>

// Use Pulser to drive built-in LED, and to turn faders on and off.
#include <Pulser.h>

// Use FadeLED subclasses to drive separate LEDs.
#include <FadeLED_Lin.h>
#include <FadeLED_Exp.h>

const byte pulser_pin = 11;

// Pins 10 and 9 support PWM on Arduino Uno and Mega.
const byte fade_lin_pin = 10;
const byte fade_exp_pin = 9;

Pulser pulser(2000, 4000);

FadeLED_Lin fade_lin(fade_lin_pin, 1500, 2000);
FadeLED_Exp fade_exp(fade_exp_pin, 1500, 2000);

void setup() {
  
  // Set built-in LED pin to output.
  pinMode(pulser_pin, OUTPUT);
  
}

void loop() {
  
  // If the pulser object updates, read its state and set the
  // states of the faders to the same.
  if (pulser.update()) {
    
    // Get the pulser's true/false state.
    bool state = pulser.read();
    
    // Set the built-in LED to on/off.
    digitalWrite(pulser_pin, state ? HIGH : LOW);
    
    // Set the faders to the same state.  A fader only changes
    // state if it's not already in that state.  Specifically,
    // if a fader is on or turning on, setting its state to
    // true won't change anything.
    fade_lin.write(state);
    fade_exp.write(state);
    
  }
  
  // Update the faders.  This is when the fading occurs if the
  // fader is turning on or off.
  fade_lin.update();
  fade_exp.update();
  
}
