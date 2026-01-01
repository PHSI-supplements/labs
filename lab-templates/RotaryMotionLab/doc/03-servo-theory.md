## Controlling a Servomotor: Theory of Operation

The servomotor is controlled with a signal that consists of periodic pulses.
The desired position of the servomotor is encoded as with width of each pulse.
This encoding, *pulse width modulation* (PWM) is sufficiently useful that most microcontrollers can be configured to generate such a signal by setting a few of their memory-mapped I/O registers.
We will not do that.
Instead, we will directly form the signal by setting an output pin to 1 or 0 as needed.
This figure shows the relevant parameters of a PWM signal:

![A periodic signal similar to a square wave, except that the peaks are not the same duration as the troughs. The time between two rising edges is labeled "signal period", and the time between a rising and a falling edge is labeled "pulse width".](images/servo/pwm.svg)

A PWM signal periodically sends a pulse. The $pulse\ width$ encodes the information being transmitted; the $signal\ period$ is how often the pulse is sent.
A servomotor expects a pulse to be sent every 20ms (20,000µs); this is the *signal period*.
The *pulse width* can vary between 500µs and 2500µs.
A 500µs pulse directs the servomotor to rotate fully clockwise,
and a 2500µs pulse directs the servomotor to rotate fully counterclockwise.
The angle varies linearly with the pulse width (for example, 1500µs is the central position).


---

|                      [⬅️](02-initializing.md)                       |      [⬆️](../README.md)      |           [➡️](04-servo-implementation.md)           |
|:-------------------------------------------------------------------:|:----------------------------:|:----------------------------------------------------:|
| [Setting up the Timer and the I/O Port Pointer](02-initializing.md) | [Front Matter](../README.md) | [Control the Servomotor](04-servo-implementation.md) |
