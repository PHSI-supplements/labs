## Control the Servomotor

- [ ] [Attach the servo to the Cow&nbsp;Pi.](BB-peripherals.md#attach-the-servo-to-the-cow-pi)
- [ ] Place both of the Cow Pi's switches in the *left* position.


### Useful Constants

There are four named constants that will be useful when controlling the servo.
- `SIGNAL_PERIOD_uS` -- the time between pulses: 20,000
- `MINIMUM_PULSE_WIDTH_uS` -- the shortest allowable pulse width, indicating fully-clockwise rotated: 500
- `MAXIMUM_PULSE_WIDTH_uS` -- the longest allowable pulse width, indicating fully-counterclockwise rotated: 2500
- `PULSE_INCREMENT_uS` -- specifies how far to move the servo in each "step": 100
  - You should be able to deduce that in our design, there are 21 positions that the servo will take 


### How You'll Specify the Servo's Position

In ProximityAlarmLab, the alarm timer's interrupt period was half of the signal period.
In this assignment, the interrupt period is a small fraction of the signal period.
This is necessary because the length of the peak (aka, the pulse) varies.

In *servomotor.c*, you'll find a global variable, `pulse_width_us`.
This variable will be used to store the desired length of the pulse;
changing its value will change the servo's position.

- [ ] In the `set_servo_pin()` function in *io_functions.c*,
  use the `ioport` pointer to set the output value on `SERVO_PIN` (pin 22) to 1 when `logic_value` is `true`, and 0 otherwise.
  - Be sure to preserve the output values on the other pins.
  > 💡 **Tip**
  >
  > If you don't remember how to set output values, review your work from ControlPanelLab.
  
- [ ] In the `handle_timer_interrupt()` function in *timer.c*, call `shape_pulse()`.
- [ ] In the `center_servo()` function in *servomotor.c*, assign the appropriate value (in microseconds) to `pulse_width_us` that corresponds to the pulse width for a servo in its central position.
  - This function is called by the starter code to center the servo whenever the program starts.


### Shaping the Pulse

In RangeFinderLab, you probably used a simple boolean variable to keep track of whether to set the output pin high or low.
In this assignment, you'll need to track time between rising edges of pulses.

> ⏳ **Time**
> 
> You do *not* need a `get_microseconds()` function in `shape_pulse()`.
> Because the timer interrupt fires every 100µs, you know that when `shape_pulse()` executes, exactly 100µs has elapsed since the last time that `shape_pulse()` executed.

In the `shape_pulse()` function in *servomotor.c*:
- [ ] Add whatever variables you need to keep track of the time since the last rising edge / time until the next rising edge / time until the next falling edge.
- [ ] Add code to update those variables by 100µs.
- [ ] When it is time for a pulse's rising edge, use `set_servo_pin()` to start the pulse.
- [ ] When it is time for a pulse's trailing edge, use `set_servo_pin()` to end the pulse.

#### Check `shape_pulse()`

- [ ] Disconnect the Cow&nbsp;Pi from your computer.
- [ ] Using your fingers, turn the servo so that the servo arm is fully deflected (it does not matter which direction).
- [ ] Compile the program, connect the Cow&nbsp;Pi to your computer, and upload the program to the Cow&nbsp;Pi.

When the program starts, the servomotor should rotate, moving the arm into its central position.


### Change the Pulse Width

- [ ] Add code to `servo_step_clockwise()` to decrease the pulse width by 100µs unless doing so would cause the pulse to be shorter than 500µs.
- [ ] Add code to `servo_step_counterclockwise()` to increase the pulse width by 100µs unless doing so would cause the pulse width to be longer than 2500µs.

#### Check changes to the pulse width

- [ ] Compile the program and upload the program to the Cow&nbsp;Pi.

The starter code will repeatedly call `servo_step_counterclockwise()` and  `servo_step_clockwise()` to step the motor back & forth through 21 positions.
Initially, it will rotate *counterclockwise*.
If it rotates clockwise first, you probably have your `servo_step_clockwise()` and `servo_step_counterclockwise()` implementations swapped.


---

|                      [⬅️](03-servo-theory.md)                       |      [⬆️](../README.md)      |                       [➡️](05-rotary-encoder-theory.md)                        |
|:-------------------------------------------------------------------:|:----------------------------:|:------------------------------------------------------------------------------:|
| [Controlling a Servomotor: Theory of Operation](03-servo-theory.md) | [Front Matter](../README.md) | [Reading the Rotary Encoder: Theory of Operation](05-rotary-encoder-theory.md) |
