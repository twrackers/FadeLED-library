# FadeLED #

The `FadeLED` library provides the ability to turn LEDs on and off with fade-in/fade-out effects, using PWM-capable GPIO pins on the Arduino-class board.  The library contains three classes.

- The *FadeLED* class is subclassed from *StateMachine* ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).  This class handles the state and timing logic which is common to the other two classes.
- The *FadeLED_Lin* class is subclassed from *FadeLED*, and provides the additional logic to perform a *linear fade* from fully off to fully on and back.  The times required for the turning-on and turning-off fades are set independently when calling the constructor.  When used to drive an LED, the linear fade mimics a light which is intentionally turned on and off slowly, such as the large red beacons which illuminate radio towers at night.  The slow fade on and off of these beacons, usually large incandescent lamps, reduces the thermal shock on their filaments, extending their lives.
- The *FadeLED_Exp* is also subclassed from *FadeLED*, and produces an *exponential fade* effect.  This mimics a large incandescent bulb which is not faded in a controlled manner, but takes a finite time to go from off to on as the filament heats up.  Similarly, this type of bulb also takes some time to go fully dark when power is removed.  Because these are thermal effects, they naturally follow exponential curves both turning on and off.

## Examples ##

The `FadeLED` library contains several example sketches in the `examples` directory.

- `SimpleLightbulb` simulates a single incandescent bulb with visible turn-on and turn-off times, using the `FadeLED_Exp` subclass.
- `LightbulbSim` simulates three incandescent bulbs with different turn-on and turn-off times.
- `BeaconSim` simulates three slow-fade lights like those used on transmitter and cell towers.  This uses the `FadeLED_Lin` subclass.
- `Faders` shows the difference in appearance between a linear and an exponential fade curve.

Examples of linear and exponential fade curves can be seen [here](extras/FadeLED_plot.png).

## Dependencies ##

*FadeLED* requires the *StateMachine* class.  *FadeLED_Lin* and *FadeLED_Exp* only require *FadeLED* and no additional classes.

## Installation ##

Instructions for installing the `FadeLED` library can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md](https://github.com/twrackers/FadeLED-library/blob/main/INSTALL.md).

## API: FadeLED ##

### *FadeLED(const byte pin, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED` object.  This constructor should not be called directly by application code, but is called by the constructors of the `FadeLED_Lin` and `FadeLED_Exp` derived classes.

#### Arguments ####

- **pin: const byte:** PWM-capable GPIO pin which will drive an LED connected to it.
- **invert: const bool:** If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` if `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).  **NOTE:** The `LED_BUILTIN` pin on the Arduino Uno is **not** PWM enabled; other boards may differ on that feature.

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED` object.  This method should not be called directly by the user's application code; it will be called by the `FadeLED_Lin` and `FadeLED_Exp` `update()` methods from the Arduino sketch's `loop()` function.

#### Returns ####

- **bool:** `true` if object's state has been updated.

### *bool read() const* ###

Gets the state of the object.

#### Returns ####

- **bool:** Returns `true` if LED is either fully on or is fading from off to on, and `false` if LED is fully off or fading from on to off.

### *void write(bool state)* ###

Sets the state of the object to either turning-on or turning-off.

#### Arguments ####

- **state: bool:**  If `true`, sets object to turning-on state, otherwise it is set to turning-off.

## API: FadeLED_Lin ##

### *FadeLED_Lin(const byte pin, const unsigned int onTime, const unsigned int offTIme, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED_Lin` object, which in turn creates an instance of the `FadeLED` base class.  The `FadeLED_Lin` object inherits the `read()` and `write()` methods from the base class.

#### Arguments ####

- **pin: const byte:** PWM-capable GPIO pin which will drive an LED connected to it.
- **onTime: const unsigned int:** Time in milliseconds that GPIO pin takes to go from fully-off to fully-on.
- **offTime: const unsigned int:** Time in milliseconds that GPIO pin takes to go from fully-on to fully-off.
- **invert: const bool:** If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` is `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED_Lin` object.  This method should be called from within the Arduino sketch's `loop()` function.

#### Returns ####

- **bool:** `true` if object's state has been updated.

## API: FadeLED_Exp ##

### *FadeLED_Exp(const byte pin, const unsigned int onTime, const unsigned int offTIme, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED_Exp` object, which in turn creates an instance of the `FadeLED` base class.  The `FadeLED_Exp` object inherits the `read()` and `write()` methods from the base class.

#### Arguments ####

- **pin: const byte:** PWM-capable GPIO pin which will drive an LED connected to it.
- **onTime: const unsigned int:** Time in milliseconds that GPIO pin takes to go from fully-off to fully-on.
- **offTime: const unsigned int:** Time in milliseconds that GPIO pin takes to go from fully-on to fully-off.
- **invert: const bool:** If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` if `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED_Lin` object.  This method should be called from within the Arduino sketch's `loop()` function.

#### Returns ####

- **bool:** `true` if object's state has been updated.
