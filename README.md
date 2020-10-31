# FadeLED #

The `FadeLED` library provides the ability to turn LEDs on and off with fade-in/fade-out effects, using PWM-capable GPIO pins on the Arduino-class board.  The library contains three classes.

- The *FadeLED* class is subclassed from *StateMachine* ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).  This class handles the state and timing logic which is common to the other two classes.
- The *FadeLED_Lin* class is subclassed from *FadeLED*, and provides the additional logic to perform a *linear fade* from fully off to fully on and back.  The times required for the turning-on and turning-off fades are set independently when calling the constructor.  When used to drive an LED, the linear fade mimics a light which is intentionally turned on and off slowly, such as the large red beacons which illuminate radio towers at night.  The slow fade on and off of these beacons, usually large incandescent lamps, reduces the thermal shock on their filaments, extending their lives.
- The *FadeLED_Exp* is also subclassed from *FadeLED*, and produces an *exponential fade* effect.  This mimics a large incandescent bulb which is not faded in a controlled manner, but takes a finite time to go from off to on as the filament heats up.  Similarly, this type of bulb also takes some time to go fully dark when power is removed.  Because these are thermal effects, they naturally follow exponential curves both turning on and off.

Examples of linear and exponential fade curves can be seen [here](extras/FadeLED_plot.png).

## Dependencies ##

*FadeLED* requires the *StateMachine* class.  *FadeLED_Lin* and *FadeLED_Exp* only require *FadeLED* and no additional classes.

## Installation ##

Instructions for installing the `FadeLED` library can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md](https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md).
