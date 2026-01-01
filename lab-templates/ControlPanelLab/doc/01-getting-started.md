## Getting Started

> 📇 **Scenario**
>
> Archie walks up to you, along with Herb Bee from Eclectic Electronics.
> Herb is holding a tangled mess of electronics. 
> Archie explains, "Herb here has developed a prototype of a device that he thinks will be useful for our physical security needs, as well as a few other applications around here. 
> He calls it the Cow Pi."
> 
> You look at the device in Herb’s hands and see the Raspberry Pi Pico central to the circuit.
> "I suppose the ‘-Pi’ suffix is because it uses a Raspberry Pi Pico?"
> Herb replies, "Um, yeah, sure. 
> We considered using an Arduino Nano, but Cowduino isn’t very punny, is it?"
> 
> Archie chimes in, "Maybe with the right emphasis: Cow-DOO-ino."
> 
> "That’s kind of subtle, don’t you think? How will people know to put the emPHAsis on that sylLAble?"
> 
> "I think we’re getting off topic here," you point out. 
> "How can I help?"
> 
> "Oh, right," Herb says,
> "We don't want application code to directly access the I/O registers.
> Instead, we'd like some functions that handle the low-level behavior, so that we can keep the application code readable."
> 
> "Sounds fun," you say.
> I'll get on it!"

During your lab period, the TAs will provide a refresher on bitmasks, both to read inputs and to use the read-modify-write pattern for outputs.
They will also discuss some subtle semantics problems that students have encountered in the past.
Finally, **the TAs will guide the class through the first modifications to the starter code that you must make.**
During the remaining time, the TAs will be available to answer questions.


### Configuring the Project

> ❗️ **Important**
> 
> These instructions differ from what you used for other assignments.
> Be sure to read them.

#### From VS Code

- [ ] Start your IDE.
- [ ] Launch the PlatformIO plugin.
- [ ] Depending on your particular IDE and plugin version, look for a button to "Pick a Folder", "Open Project", or something similar.
- [ ] Click on that button and navigate to the ControlPanelLab project.
- [ ] Build the project.
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.

#### From the Command Line

- [ ] Use the `cd` command to navigate to the ControlPanelLab directory
- [ ] Build the project using the command
  ```shell
  pio run
  ```
  - There are many parts of MBED&nbsp;OS that generate compiler warnings.
    By building the project now, before you've written any of your own code, you're assured that any compiler warnings that you see in the future will be warnings about *your* code.


### Modes of Operation

The mode of operation is determined by the position the right switch is in when the Cow&nbsp;Pi is powered-up or reset.


#### Test Keypresses and Time

- **right switch** in the *right* position

In this mode, the Cow&nbsp;Pi's display will show:

```
KEYPRESS    TIME
 NO    0.125260s
```

Whenever a key is pressed, the display will change `NO` to `YES`.
When that key is released, the display will change `YES` to `NO`.

Whenever a key is pressed or released, whenever a button is pressed or released, and whenever a switch is toggled,
the display will update to show the time elapsed since the microcontroller was powered up.


#### Test Inputs and Outputs

- **right switch** in the *left* position

In this mode, the display module will show:
```
KEY   BTN   SW
 -    U U   R L
```

The display will show whether the buttons are pressed ("D" for down) or not ("U" for up)
and the positions of thw switches ("L" for left, "R" for right).
The code that determines which key (if any) on the numeric keypad is pressed will work after you write a small amount of code [during labtime](03-labtime.md#populate-the-keypads-lookup-table), which the TAs will guide you through.
Each LED will illuminate when the corresponding switch is in the right position and the corresponding button is pressed.


### Descriptions of ControlPanelLab Files

#### io_functions.h & io_functions.c

Do not edit *io_functions.h*.

The *io_functions.c* file contains the code that you will edit.
The functions that read the inputs and write to the outputs currently make use of CowPi library functions.
Your task will be to replace those library calls with code that uses the microcontroller's memory-mapped I/O registers.

#### display.h & display.cpp

Do not edit *display.h* or *display.cpp*.

These files contain code to drive the Cow Pi's display.

#### control_panel.c

Do not edit *control_panel.c*.

This file contains the driver code for the assignment.
As is common in embedded systems, after the program has been initialized, this assignment's program runs in an infinite loop:

```c
void setup() {
    initialize_board(); /* Summarizing several lines of code */
    initialize_io(cowpi_right_switch_is_in_right_position());
}

void loop() {
    test_io();
    count_visits(7);
}

int main() /* Not included in control_panel.c; provided by the framework */ {
    setup();
    while(true) {
        loop();
    }
}
```

---

|                 |      [⬆️](../README.md)      |            [➡️](02-debouncing-debugging.md)            |
|:---------------:|:----------------------------:|:------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Debouncing and Debugging](02-debouncing-debugging.md) |
