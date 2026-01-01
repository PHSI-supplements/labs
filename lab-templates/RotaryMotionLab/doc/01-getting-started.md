## Getting Started

> 📇 **Scenario**
>
> "The problem that we have," Archie explains, "is that some of our specimens can be damaged when handled by humans."
> 
> You think about all the teeth and claws and beaks and talons and tusks and fangs that you've seen at the Pleistocene Petting Zoo.
> "The *animals* can be harmed by *us*?"
> 
> "Well, yes.
> Thanks to the Proximity Alarm, Combination Locks, and the like, we're pretty safe from the animals.
> I mean, what could *possibly* go wrong?
>
> "But when they're young," Archie continues, "some of the specimens can be hurt by one of our technicians holding them too tightly,
> or they might catch disease from some human-carried germ that didn't exist millennia ago.
> So I'd like you to prototype a remotely-manipulated arm.
> We could attach that to a robot, and then we can take care of our young specimens without any risk at all."

### Configuring the Project

#### From VS Code

- [ ] Start your IDE.
- [ ] Launch the PlatformIO plugin.
- [ ] Depending on your particular IDE and plugin version, look for a button to "Pick a Folder", "Open Project", or something similar.
- [ ] Click on that button and navigate to the RotaryMotionLab project.
- [ ] Build the project.
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.

#### From the Command Line

- [ ] Use the `cd` command to navigate to the RotaryMotionLab directory
- [ ] Build the project using the command
  ```shell
  pio run
  ```
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.


### Modes of Operation

The mode of operation is determined by the positions of the switches when the Cow&nbsp;Pi is powered-up or reset.


#### Test the servo control

- Both switches in the *left* position.

In this mode, the servo will repeatedly move back and forth in small increments.

#### Test the rotary encoder

- **Right** switch in the *left* position, and the **left** switch in the *right* position.

In this mode, the display module will show how many times the rotary encoder has been turned clockwise and how many times it's been turned counterclockwise.

#### "Remotely" control the servo using the rotary encoder

- **Right** switch in the *right* position.

We have included code that will use your code to incrementally turn the servo each time that you incrementally turn the rotary encoder, and in the same direction that you turn the rotary encoder.


### Descriptions of RotaryMotionLab Files

#### timer.h & timer.c

Do not edit *timer.h*.

The *timer.c* file contains a function to configure a timer interrupt and register its ISR, and a function that will serve as the ISR.

#### io_functions.h & io_functions.c

Do not edit *io_functions.h*.

The *io_functions.c* file contains functions to read input from the rotary encoder and to set the logic value on the output pin connected to the servo.

#### servomotor.h & servomotor.c

Do not edit *servomotor.h*.

The *servomotor.c* file contains a function that is called by the timer's ISR to shape the pulse sent to the servo, 
and functions to change the desired rotational position for the servo.

#### rotary-encoder.h & rotary-encoder.c

Do not edit *rotary-encoder.h*.

The *rotary-encoder.c* file contains a function that is called by the timer's ISR to sample the rotary encoder's input, 
and a function to report the direction that the rotary encoder is being turned.

#### display.h & display.cpp

Do not edit *display.h* or *display.cpp*.

These files contain code to drive the Cow Pi's display.

#### interrupt_support.h & interrupt_support.cpp

Do not edit *interrupt_support.h* or *interrupt_support.cpp*.

These files provide functions to configure interrupts and register interrupt service routines (`register_pin_ISR()` & `register_periodic_timer_ISR()`)
and to reset a timer interrupt (`reset_periodic_timer()`)

#### remotely-manipulated-arm.c

Do not edit *remotely-manipulated-arm.c*.

This file contains the driver code for the assignment.


---

|                 |      [⬆️](../README.md)      |                      [➡️](02-initializing.md)                       |
|:---------------:|:----------------------------:|:-------------------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Setting up the Timer and the I/O Port Pointer](02-initializing.md) |
