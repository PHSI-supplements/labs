## Reading the Rotary Encoder: Theory of Operation

### Rotary Encoder

The rotary encoder consists of a shaft that can rotate without stop in either direction, and detents that hold the shaft in position when you are not rotating it.
Electrically, it has a pair of wipers, each of which is connected to a pin at one end, and which share a common pin at the other end. 
By connecting the common pin to ground (as we have) and connecting the wipers’ pins to pulled-up input pins on the microcontroller (as we have), then we can read the logic values of the wipers. 
As the shaft rotates, the pair of wipers each cycle through a square wave. 
The two wipers’ square waves form a quadrature; 
that is, they are 90°out of phase with each other, as shown below.

![Two square waves, 90º out of phase with each other. Arrows indicate that clockwise rotation requires reading the timing diagram from right-to-left; counterclockwise, left-to-right.](images/rotary-encoder/quadrature.svg)

By tracking which pin changes value first or second, we can determine which direction the shaft is rotating.


### Sampling

In CalculatorLab, you polled inputs to determine when to respond to an input.
In ProximityAlarmLab, you configured a pin interrupt to fire in response to an input, and you responded to the input in the ISR.
In this assignment, you will *sample* an input.

Sampling has properties of both polling and handling interrupts.
As with polling, you will read the input pins to determine whether action needs to be taken.
Unlike conventional polling, you will read the input as part of handling an interrupt -- specifically, as part of handling a timer interrupt.

When handling a pin interrupt, the ISR runs within a few clock cycles of the input, a little over 100ns in the worst case.
When polling in the main control loop, the timing of detecting the input is unpredictable;
your program might even miss a fast-changing input.
For slow-moving inputs like pressing and releasing a button, that's not a problem --
but even though the rotary encoder is a human-scale input, progressing through the quadrature's phases is still fast enough that a transition might be missed with polling in the main loop.

With sampling, the ISR runs very predictably -- in our case, every 100µs.
For an input like the rangefinder, this would limit the precision with which we could measure distance.
For a human-scale input, it's fine (unless you turn the rotary encoder's shaft faster than 6250rpm).


---

|           [⬅️](04-servo-implementation.md)           |      [⬆️](../README.md)      |           [➡️](06-rotary-encoder-implementation.md)            |
|:----------------------------------------------------:|:----------------------------:|:--------------------------------------------------------------:|
| [Control the Servomotor](04-servo-implementation.md) | [Front Matter](../README.md) | [Read the Rotary Encoder](06-rotary-encoder-implementation.md) |
