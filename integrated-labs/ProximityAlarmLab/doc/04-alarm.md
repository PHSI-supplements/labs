## Generating an Alarm

An alarm consists of a chirp from the piezobuzzer and a strobe of the LEDs.

### Constant Tone

The `manage_alarm()` function runs in the program's main control loop.
When you examine it, you'll see that it has input state machines for the two pushbuttons.
In this section, you will make it possible for the right pushbutton to generate a continuous tone.
Notice that when the right pushbutton responds to a press, it sets `sound_alarm` to `true`.

#### Control the LEDs.

- [ ] In `handle_alarm_timer()`, add code that illuminates the left and right LEDs when `sound_alarm` is true,
  and that deluminates the left and right LEDs when `sound_alarm` is false.
  
  > 💡 **Tip**
  > 
  > Use `cowpi_illuminate_left_led()`, `cowpi_illuminate_right_led()`, `cowpi_deluminate_left_led()`, and `cowpi_deluminate_right_led()`

  > ⓘ **Note**
  >
  > Obviously, this doesn't need a timer interrupt, but it can establish that the interrupt is firing and being handled.
  > It also will be coherent with the code that *does* need the interrupt. 

- [ ] [Attach the Piezobuzzer Module to the Cow Pi](BB-peripherals.md#attach-the-piezobuzzer-module-to-the-cow-pi).
- [ ] Place both switches in the *left* position.
  Compile and upload the program to the Cow Pi.
- [ ] Confirm that the LEDs turn on when you press the **left** pushbutton and that they turn off when you release the pushbutton.

#### Generate a tone

Recall that the tone has a period of 1000µs and that the timer interrupt has a period of 500µs.
On alternating interrupts, we want the tone to transition from trough-to-peak and peak-to-trough.

- [ ] At the start of `handle_alarm_timer()`, add a variable to keep track of whether the tone's current phase is a peak or a trough.

  > 💡 **Tip**
  >
  > Declare the variable to be `static` so that its value is preserved between invocations of `handle_alarm_timer()`.

- [ ] Add code to `handle_alarm_timer()` to alternate that variable between indicating a peak and indicating a trough.
- [ ] Add code to `handle_alarm_timer()` that, when `sound_alarm` is `true`,
  sets the value on the `BUZZER_PIN` pin to high when the tone is in its peak phase,
  and sets the value on the `BUZZER_PIN` pin to low when the tone is in its trough phase.

  > 💡 **Tip**
  >
  > Use `set_pin_high()` and `set_pin_low()`.

- [ ] Double-check that both switches in the *left* position.
  Compile and upload the program to the Cow Pi.
- [ ] Confirm that the piezobuzzer generates a 1kHz tone (and the LEDs turn on) when you press the **left** pushbutton and that the piezobuzzer is silent (and the LEDs turn off) when you release the pushbutton.


### Chirping the Piezobuzzer and Strobing the LEDs

The `manage_alarm()` function has input state machines for the two pushbuttons.
In this section, you will build on the code for the continuous tone to make it possible for the left pushbutton to emit a brief chirp while the LEDs emit a quick blink.
Notice that when the left pushbutton responds to a press, it calls the `chirp()` function.
Notice also that there is a `silence_buzzer_at` global variable that you have not yet used.

- In `chirp()`:
  - [ ] Add code to set `sound_alarm` to `true`.
  - [ ] Add code to set `silence_buzzer_at` to 100,000µs (0.1s) after the current time.

  > 💡 **Tip**
  >
  > Use `get_microseconds()`.

- [ ] In `handle_alarm_timer()`, add code that sets `sound_alarm` to `false` if the current time is after the time specified with `silence_buzzer_at`.

- [ ] Double-check that both switches in the *left* position.
  Compile and upload the program to the Cow Pi.
- [ ] Confirm that when you press the **right** pushbutton, the piezobuzzer emits a tone and the LEDs illuminate for a tenth of a second and go silent and dark after that.


---

|                 [⬅️](03-piezobuzzer-intro.md)                  |      [⬆️](../README.md)      |                 [➡️](05-distance.md)                  |
|:--------------------------------------------------------------:|:----------------------------:|:-----------------------------------------------------:|
| [Generating Tones with a Piezobuzzer](03-piezobuzzer-intro.md) | [Front Matter](../README.md) | [Measuring the Distance to an Object](05-distance.md) |
