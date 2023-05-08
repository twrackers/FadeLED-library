# FadeLED #

----------

The `FadeLED` library provides the ability to turn LEDs on and off with fade-in/fade-out effects, using PWM-capable GPIO pins on the Arduino-class board.  The library contains three classes.

- The *FadeLED* class is subclassed from *StateMachine* ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).  This class handles the state and timing logic which is common to the other two classes.
- The *FadeLED_Lin* class is subclassed from *FadeLED*, and provides the additional logic to perform a *linear fade* from fully off to fully on and back.  The times required for the turning-on and turning-off fades are set independently when calling the constructor.  When used to drive an LED, the linear fade mimics a light which is intentionally turned on and off slowly, such as the large red beacons which illuminate radio towers at night.  The slow fade on and off of these beacons, usually large incandescent lamps, reduces the thermal shock on their filaments, extending their lives.
- The *FadeLED_Exp* class is also subclassed from *FadeLED*, and produces an *exponential fade* effect.  This mimics a large incandescent bulb which is not faded in a controlled manner, but takes a finite time to go from off to on as the filament heats up.  Similarly, this type of bulb also takes some time to go fully dark when power is removed.  Because these are thermal effects, they naturally follow exponential curves both turning on and off.
- The *FadeLED_Func* class is also subclassed from *FadeLED*.  It defines no specific fade effect, but allows the calling code to create an arbitray one.  This is done by callig the *get()* method after updating the object, which will return a value of type *double* between 0.0 and 1.0, where 0.0 is fully off and 1.0 is fully on.  A new value in this range is then computed and passed back to the object with the *set()* method, to be converted to the appropriate byte value and written to the PWM analog output.  See the *Lighthouse* example code to see how this can be done.

## Examples ##

The `FadeLED` library contains several sketches in the `examples` directory.

- `SimpleLightbulb` simulates a single incandescent bulb with visible turn-on and turn-off times, using the `FadeLED_Exp` subclass.
- `LightbulbSim` simulates three incandescent bulbs with different turn-on and turn-off times.
- `BeaconSim` simulates three slow-fade lights like those used on transmitter and cell towers.  This uses the `FadeLED_Lin` subclass.
- `Faders` shows the difference in appearance between a linear and an exponential fade curve.
- `Lighthouse` shows how the `FadeLED_Func` can create a custom fade curve.

Examples of linear and exponential fade curves can be seen [here](extras/FadeLED_plot.png).

## Dependencies ##

*FadeLED* requires the *StateMachine* class.  *FadeLED_Lin*, *FadeLED_Exp*, and *FadeLED_Func* only require *FadeLED* and no additional classes.

## Installation ##

Instructions for installing the `FadeLED` library can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md](https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md).
