# Libraries
You will find here some Arduino libraries I've developed. All are open source and free to use by anyone.

__RingBuffer__ implements a _ring buffer_ or _FIFO_ (first in first out) of bytes.  This is useful in communications code where data might arrive in bursts more quickly than they can be processed, as long as in the long run they don't come in too fast for the application.

__StateMachine__ is a simple Finite State Machine (FSM) class library.  It is a base class designed to be subclassed into FSMs that solve specific tasks.  Example derived classes of StateMachine are:

* __FadeLED__ can be used to turn an LED on and off with slow fades between full-on and full-off.
* __Pulser__ will periodically alternate between two states with separate on and off times.
* __SlowSwitcher__ can switch alternately between two states, with a settable dead time during state switches when it's in neither state.
  
More info on each is in its README file.
