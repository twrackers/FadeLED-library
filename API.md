# FadeLED library API #

## FadeLED (base class) ##

### *FadeLED(const byte pin, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED` object.  This constructor should not be called directly by application code, but is called by the constructors of the `FadeLED_Lin` and `FadeLED_Exp` derived classes.

#### Arguments ####

- *pin: const byte*: PWM-capable GPIO pin which will drive an LED connected to it.
- *invert: const bool*: If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` if `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).  **NOTE:** The `LED_BUILTIN` pin on the Arduino Uno is **not** PWM enabled; other boards may differ on that feature.

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED` object.  This method should not be called directly by the user's application code; it will be called by the `FadeLED_Lin` and `FadeLED_Exp` `update()` methods from the Arduino sketch's `loop()` function.

#### Returns ####

- *bool*: `true` if object's state has been updated.

### *bool read() const* ###

Gets the state of the object.

#### Returns ####

- *bool*: Returns `true` if LED is either fully on or is fading from off to on, and `false` if LED is fully off or fading from on to off.

### *void write(bool state)* ###

Sets the state of the object to either turning-on or turning-off.

#### Arguments ####

- *state: bool*: If `true`, sets object to turning-on state, otherwise it is set to turning-off.

## FadeLED_Lin ##

### *FadeLED_Lin(const byte pin, const unsigned int onTime, const unsigned int offTIme, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED_Lin` object, which in turn creates an instance of the `FadeLED` base class.  The `FadeLED_Lin` object inherits the `read()` and `write()` methods from the base class.

#### Arguments ####

- *pin: const byte*: PWM-capable GPIO pin which will drive an LED connected to it.
- *onTime: const unsigned int*: Time in milliseconds that GPIO pin takes to go from fully-off to fully-on.
- *offTime: const unsigned int*: Time in milliseconds that GPIO pin takes to go from fully-on to fully-off.
- *invert: const bool*: If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` is `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED_Lin` object.  This method should be called from within the Arduino sketch's `loop()` function.

#### Returns ####

- *bool*: `true` if object's state has been updated.

## FadeLED_Exp ##

### *FadeLED_Exp(const byte pin, const unsigned int onTime, const unsigned int offTIme, const bool invert = false)* ###

The constructor creates an instance of a `FadeLED_Exp` object, which in turn creates an instance of the `FadeLED` base class.  The `FadeLED_Exp` object inherits the `read()` and `write()` methods from the base class.

#### Arguments ####

- *pin: const byte*: PWM-capable GPIO pin which will drive an LED connected to it.
- *onTime: const unsigned int*: Time in milliseconds that GPIO pin takes to go from fully-off to fully-on.
- *offTime: const unsigned int*: Time in milliseconds that GPIO pin takes to go from fully-on to fully-off.
- *invert: const bool*: If `false`, the GPIO pin will be driven `HIGH` when the `FadeLED` object goes to its *on* state; the Arduino's `LED_BUILTIN` turns on when its pin is set `HIGH`.  If `invert` if `true`, the *on* state drives the GPIO pin `LOW`.  The default is `false` (don't invert).

### *virtual bool update()* ###

Checks if it is time to update the state of the `FadeLED_Lin` object.  This method should be called from within the Arduino sketch's `loop()` function.

#### Returns ####

- *bool*: `true` if object's state has been updated.
