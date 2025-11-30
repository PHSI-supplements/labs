## Read the Rotary Encoder

- [ ] [Attach the rotary encoder module to the Cow&nbsp;Pi.](BB-peripherals.md#attach-the-rotary-encoder-module-to-the-cow-pi)
- [ ] Place the **right** switch in the *left* position, and the **left** switch in the *right* position.


### How the Program will get the Direction of Rotation

Our design uses two cooperating functions (in addition to the function that uses memory-mapped I/O).
In *rotary-encoder.c*, you'll find a global variable, `direction`.
The first function responds to a timer interrupt and samples the input to set `direction`.
The second function runs in the main control loop and returns `direction`'s value.

First, though, we have some preliminaries.

In the `get_quadrature()` function in *io_functions.c*:
- [ ] Use the `ioport` pointer to read the inputs values on `A_WIPER_PIN` (pin 17) and on `B_WIPER_PIN (pin 16) at the same time.
  > 💡 **Tip**
  >
  > If you don't remember how to read input values, review your work from ControlPanelLab.
  
  > ❗️ **Important**
  >
  > Read the values on both pins in a single read, to ensure that you don't read one pin before a phase change and the other pin after the phase change.
- [ ] Return the quadrature value.
  - You may leave the value in bits 17..16, or you may shift them to occupy bits 1..0.
  > ❗️ **Important**
  >
  > Do ***not*** use `cowpi_debounce_long()` (or any of the other debouncing functions in the CowPi library)!
  > The debouncing functions in the CowPi library use the gold standard of requiring an input to be stable for 20ms before treating its value as valid.
  > You will be able to turn the rotary encoder's shaft from one detent to the next in less than 20ms.

In the `handle_timer_interrupt()` function in *timer.c*:
- [ ] Call `sample_rotary_encoder()`.


### Sampling the Input

In the `sample_rotary_encoder()` function in *rotary-encoder.c*:
- [ ] Create a variable to store the *previous* quadrature value.
- [ ] Create a variable to store the *current* quadrature value.
- [ ] Call `get_quadrature()` to get the current quadrature value.

For the purposes of discussion, we will refer to the quadrature value by the two bits, `A B`.
For example, the value `1 0` refers to the quadrature phase in which `A_WIPER_PIN` is logic-high and `B_WIPER_PIN` is logic-low. 

If you examine the timing diagram on [the previous page](05-rotary-encoder-theory.md),
you'll notice that at each phase transition, the combination of the new phase and the old phase can tell you which direction the shaft is being rotated.
We will make the determination when the rotary encoder transitions into `0 0`.

- [ ] Add an `if` statement to check whether the current quadrature value is `0 0` and the direction is `STATIONARY`.
- If the quadrature's value is `0 0`, then the previous value must have been `1 0`, `0 1`, or `0 0`.
  If the current and previous value are the same, then we are not looking at a phase transition, so we can ignore that combination.
- [ ] In that `if` statement (in which the current quadrature value is `0 0`), use the previous quadrature value to determine whether the rotary encoder's shaft is rotating `CLOCKWISE` or `COUNTERCLOCKWISE`,
  and set `direction` accordingly.
  > 💡 **Tip**
  >
  > Look at the "clockwise" and "counterclockwise" arrows in the timing diagram on [the previous page](05-rotary-encoder-theory.md)
  > to help you determine the previous phase's quadrature value for each of the two directions.

- [ ] At the end of `sample_rotary_encoder()`, update the previous quadrature value with the current quadrature value.


### Reporting the Direction

The `get_direction()` function has two jobs.
Its primary responsibility is to report the direction of rotation.
It must also make sure that it does not report `CLOCKWISE` or `COUNTERCLOCKWISE` twice (or a million times) for a single turn of the shaft from one detent to the next.

- [ ] Add code to make note of `direction`'s value.
- [ ] Set `direction` to `STATIONARY`.
- [ ] Return the direction.

If `direction` already was `STATIONARY`, then setting it to `STATIONARY` has no effect, and `get_direction()` will continue to correctly report that the shaft is not turning.
On the other hand, if `direction` wasn't `STATIONARY`, then `get_direction()` will report the non-stationary direction once,
and in subsequent calls, it will return `STATIONARY` until the shaft is turned again.


### What About Debouncing?

For a very slow turn (about 300rpm), switch bounce will always result in current/previous quadrature values that correspond to adjacent phases.
For a more typical turn, switch bounce will typically result in current/previous quadrature values that do not correspond to valid phase changes, and our design does nothing for those combinations, so they have no effect.

It is still possible that a bounce-induced pair of values corresponds to adjacent phases.
We only care about transitions into `0 0`.
Without loss of generality, suppose that we transition into `0 0` in the `CLOCKWISE` direction.
The only adverse possibility is if we transition into the subsequent phase and then have switch bounce cause it to appear as though we transitioned back into `0 0` briefly.
The logic inside the `if` statement would interpret that as `COUNTERCLOCKWISE`;
however, we had already set `direction` to `CLOCKWISE`, and so the logic inside the `if` statement wouldn't run because the `if` statement's condition checks whether `direction` is `STATIONARY`.

> 🏎️ **A Race Condition**
> 
> There is a race condition.
> If `get_direction()` is called while the rotary encoder's wipers are still bouncing,
> then you could see a single turn produce what appears to be one turn in both directions
> or what appears to be two `CLOCKWISE` turns (or two `COUNTERCLOCKWISE turns).
> 
> We are choosing to ignore this race condition for now because losing the race is a low-probability/low-impact event.
> If enough students see this race lost, then I'll update this assignment in future semesters with a slightly more-complex detection design that will always ignore spurious phase changes.


### Test Your Code

- [ ] Compile the program and upload the program to the Cow&nbsp;Pi.

The program will show
```
CCW   0  CW   0
```
on the top row of the display.
As you turn the rotary encoder's shaft clockwise, the `CW` number will increase by 1 for each detent;
as you turn the shaft counterclockwise, the `CCW` number will increase by 1 for each detent.

- [ ] Turn the knob each direction several turns to confirm the correct behavior.


---

|                       [⬅️](05-rotary-encoder-theory.md)                        |      [⬆️](../README.md)      |            [➡️](07-input-to-actuator.md)             |
|:------------------------------------------------------------------------------:|:----------------------------:|:----------------------------------------------------:|
| [Reading the Rotary Encoder: Theory of Operation](05-rotary-encoder-theory.md) | [Front Matter](../README.md) | [Remotely Operating an Arm](07-input-to-actuator.md) |
