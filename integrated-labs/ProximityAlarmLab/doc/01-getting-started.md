## Getting Started

> 📇 **Scenario**
>
> "I have various teams working on different projects around here to improve security," Archie reminds you.
> He glances toward the Zoo’s labs, where there’s now a guy who looks like the actor who portrayed the fictional actor who portrayed the Norse god Odin,
> trying to avoid children while wistfully talking about raising rabbits in Montana.
> You briefly wonder why there are children someplace where there are also carnivorous megafauna,
> and then you remember that you work at a petting zoo.
> "What I need your team to do," Archie continues, 
> "is make a range finder that will alert us when someone – or something – gets too close to someplace they shouldn’t be."

### Configuring the Project

#### From VS Code

- [ ] Start your IDE.
- [ ] Launch the PlatformIO plugin.
- [ ] Depending on your particular IDE and plugin version, look for a button to "Pick a Folder", "Open Project", or something similar.
- [ ] Click on that button and navigate to the CalculatorLab project.
- [ ] Build the project.
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.

#### From the Command Line

- [ ] Use the `cd` command to navigate to the CalculatorLab directory
- [ ] Build the project using the command
  ```shell
  pio run
  ```
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.


### Modes of Operation

The mode of operation is determined by the positions of the switches when the Cow&nbsp;Pi is powered-up or reset.


#### Develop and Test Alarm Code

- Both switches in the *left* position.

In this mode, the code that you write will cause the LEDs to illuminate and a 1kHz tone to sound whenever you press the **right** pushbutton.
When you press the **left** pushbutton, the buzzer will chirp, and the LEDs will strobe.


#### Develop and Test Rangefinder Code

- **Right** switch in the *left* position, and the **left** switch in the *right* position.

In this mode, the code that you write will cause the rangefinder to emit an ultrasonic pulse.
If an echo is detected, then there must have been an object that reflected the pulse.
Knowing the time elapsed between the start and end of the pulse will tell you how far away the object is.


#### Proximity Alarm

- **Right** switch in the *right* position.

We have included the code for a simple proximity alarm that makes use of the alarm and rangefinder code that you will write.
After you have correctly implemented those, you will not need to implement any further code for the proximity alarm.


### Descriptions of CalculatorLab Files

#### common.h

Do not edit *common.h*.

The *common.h* file has four `static inline` functions that you can use to get the current time (`get_microseconds()`) 
and to quickly get/set pin values (`read_pin()`, `set_pin_high()`, and `set_pin_low()`). 

#### display.h & display.cpp

Do not edit *display.h* or *display.cpp*.

These files contain code to drive the Cow Pi's display.

#### interrupt_support.h & interrupt_support.cpp

Do not edit *interrupt_support.h* or *interrupt_support.cpp*.

These files provide functions to configure interrupts and register interrupt service routines (`register_pin_ISR()` & `register_periodic_timer_ISR()`)
and to reset a timer interrupt (`reset_periodic_timer()`)

#### alarm.h & alarm.c

Do not edit *alarm.h*.

The *alarm.c* file contains several functions.
`initialize_alarm()` is where you will configure a timer interrupt and register its ISR.
`manage_alarm()` runs in the main control loop to respond to user input; it also calls `chirp()`.
`handle_alarm_timer()` is the interrupt service routine that gets invoked whenever the timer interrupt fires.

#### sensor.h & sensor.c

Do not edit *sensor.h*.

The *sensor.c* file contains several functions.
`initialize_sensor()` is where you will configure a timer interrupt and register its ISR, and where you will configure a pin interrupt and register its ISR.
`manage_alarm()` runs in the main control loop to respond to user input; it also calls `initiate_pulse()` and `process_detection()`.
`on_pulse_edge()` is the interrupt service routine that gets invoked whenever the pin interrupt fires, and `handle_sensor_timer()` is the interrupt service routine that gets invoked whenever the timer interrupt fires.
`compute_distance()` is where you will compute the distance to a detected object; the starter code includes an implementation of `read_temperature_register()` to provide one of the data you need to compute the distance.

#### sentry.h & sentry.c

Do not edit *sentry.h* or *sentry.c*.

These files contain the code for the proximity alarm that is a client to your code in *alarm.c* and *sensor.c*.

#### proximityalarmlab.c

Do not edit *proximity-alarm.c*.

This file contains the driver code for the assignment.


---

|                 |      [⬆️](../README.md)      |                 [➡️](02-interrupts.md)                  |
|:---------------:|:----------------------------:|:--------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Interrupt-Driven Input/Output](02-interrupts.md) |
