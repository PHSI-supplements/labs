## Compile a Program

> ❗️ **Important**
>
> If you have not already completed Prelab 2, please complete Prelab 2 first!

> 📝 **Grading Note**
>
> To receive credit for Prelab 8, you will need to complete [the assignment on Canvas](https://mynu.instructure.com/courses/13509/assignments/1028633).


We will use PlatformIO to work with the Cow&nbsp;Pi development boards.

### About PlatformIO and the Arduino Framework

PlatformIO is able to work with many frameworks; for the I/O labs, we will use the Arduino framework. 
As application programmers, the starting point is a program with two functions, `setup()` and `loop()`, along with any helper code that you need. 
PlatformIO will compile your program and link it to a `main()` function that looks something like:

```c
int main(void) {
    setup();
    while(true) {
        loop();
    }
}
```

### Open the PlatformIO Project

- [ ] Review the instructions to configure, compile, and upload Cow&nbsp;Pi code
  - In the [terminal](../../documentation/workflow/terminal/working-on-the-lab.md#configuring-compiling-and-uploading-cow-pi-code)
  - Using [CLion](../../documentation/workflow/clion/working-on-the-lab.md#openingconfiguring-compiling-and-uploading-cow-pi-code)
  - Using [VS Code](../../documentation/workflow/vscode/working-on-the-lab.md#openingconfiguring-compiling-and-uploading-cow-pi-code)
- If you are working in the terminal:
  - [ ] Launch the course container in the terminal with `docker compose run --rm csce231`
  - [ ] In the course container, run `cd HwPreLab`
- If you are using an IDE:
  - [ ] Launch the IDE and connect it to the course container
  - [ ] Follow the instructions for your IDE to open the project
    - [CLion](../../documentation/workflow/clion/working-on-the-lab.md#openingconfiguring-the-project-cow-pi-code)
    - [VS Code](../../documentation/workflow/vscode/working-on-the-lab.md#openingconfiguring-the-project-cow-pi-code)

### Compile the Program

- If you are working in the terminal:
  - [ ] [Run the command](../../documentation/workflow/terminal/working-on-the-lab.md#compiling-the-project-cow-pi-code)
    ```bash
    pio run
    ```
- If you are using CLion:
  - [ ] [Click on the hammer icon](../../documentation/workflow/clion/working-on-the-lab.md#compiling-the-project-cow-pi-code) in the configuration bar at the top of CLion's window.
- If you are using VS Code:
  - [ ] [Click on the checkmark icon](../../documentation/workflow/vscode/working-on-the-lab.md#compiling-the-project-cow-pi-code) in the toolbar at the bottom of VS Code's window.


### Upload the Program

- [ ] Activating the bootloader requires a specific sequence of actions:

  1. Press the RESET button, located between the white breadboard and the green Raspberry Pi Pico
  2. While still pressing the RESET button, press the BOOTSEL button on the Raspberry Pi Pico
  3. Release the RESET button
  4. Release the BOOTSEL button

- [ ] Drag & drop *prelab8-yyyymmdd-hhmm.uf2* from the [build/](../build) directory into the mass storage device.

> ⓘ **Note**
>
> You will need to use your host operating system's file system to upload the file.
> The course container does not have access to your computer's USB ports.


### What You Will See

The Cow&nbsp;Pi's display will show information about the tooling used to build the program.


## Familiarize Yourself with the Debugging Help

Because of USB driver issues on Windows systems (particularly Windows&nbsp;11), 
we have provided alternatives to `printf()` debugging statements that make use of the Cow&nbsp;Pi's display.


### Liveness Counter

Observe that in the lower-right corner of the display, there is a counter that cycles through the 256 values possible with two hex-digits. If this counter stops, one of three things is true:

1. If it stops in the first few milliseconds after power-up (or if it never starts),
    then you have the Green Blinky of Death.
    You can confirm this by looking at the green LED on the Raspberry Pi Pico.
    Press the RESET button once or twice.
    Maybe three times.
    Four should definitely do it.
    Perhaps five presses.
2. If it stops after the splash screen goes away and the green LED on the Raspberry Pi Pico is blinking,
    then your program has the equivalent of a segmentation fault or some other state that caused the system to "panic."
3. If it stops and the green LED on the Raspberry Pi Pico is *not* blinking,
    then your program has code that blocks further execution.

- [ ] You can see an example of the third case by pressing your Cow Pi's **left pushbutton**.


### Display Debugging Strings

Open *prelab8.c* and look at the first if statement in the `loop()` function.
Suppose that you wanted to determine which path is taken. 
If the LEDs aren't being used for anything else, one option is to use the LEDs to indicate the path, as has already been done here.

Another option is to display a string. 
We have provided a function
```c
void display_string(int row, char const string[])
```
which can be used to do just that.
The display has eight rows, numbered 0-7, with 0 at the top.
Each row can display up to sixteen characters.

- [ ] In the `if` path, add this line of code:
    ```c
    display_string(7, "left position");
    ```

That is an example of displaying a string literal.
You can also use `sprintf()` to generate a string.

- [ ] Notice that we have already created a buffer.
    In the `else` path, add these lines of code:
    ```c
    sprintf(buffer, "line %d", __LINE__);
    display_string(7, buffer);
    ```
- [ ] Compile the program and upload it to the Cow Pi.
- [ ] Toggle the **left switch** back and forth to see the two different messages.


### Counting Visits

Suppose that you want to know whether a path has been followed once or many times. 
We have provided another function
```c
void count_visits(int row)
```
that keeps track of the number of times it has been called for a particular row and displays that counter in the last two columns of that row.
For example, the liveness counter previously mentioned is a call to `count_visits(7)` at the end of the `loop()` function.

- [ ] Change the display code in the `if` path to:
    ```c
    display_string(5, "left position");
    count_visits(5);
    ```
- [ ] Change the display code in the `else` path to:
    ```c
    sprintf(buffer, "line %d", __LINE__);
    display_string(6, buffer);
    count_visits(6);
    ```

(Notice that we have changed the rows that these will be displayed on.)

- [ ] Compile the program and upload it to the Cow Pi. 
- [ ] Toggle the **left switch** back and forth to see the two new counters update accordingly.


### The Display is Buffered

Now look at the second `if` statement, the one that checks whether the **left button** is pressed.
- [ ] In that `if` block, before the `for (;;)` line, add this line of code:
    ```c
    display_string(4, "stuck");
    ```
- [ ] Compile the program and upload it to the Cow Pi.
- [ ] After the program is running, press the **left button**.
- [ ] Notice that the liveness counter stopped, but the "stuck" message wasn't displayed.

You may recall that on a regular computer system, the standard output is buffered, 
so `printf()` can be problematic when trying to localize code that crashes a program. 
On a regular computer system, you can overcome that by flushing the standard output with `fflush(stdout)` or by printing to `stderr` instead with `fprintf(stderr, ...)`.

Similarly, `display_string()` buffers the output -- it accumulates updates until one of three things happen:

1. A call to `refresh_display()` will force the display to be updated:
    ```c
    display_string(4, "stuck");
    refresh_display();
    ```
2. A call to `count_visits()` will force the display to be updated:
    ```c
    display_string(4, "stuck");
    count_visits(4);
    ```
    The `count_visits(7)` call at the end of the `loop()` function takes care of this for most situations.
3. Ending a string with a newline character will force the display to be updated:
    ```c
    display_string(4, "stuck\n");
   ```

- [ ] Try each of those options and confirm for yourself that they will allow the "stuck" message to be displayed.


## You Are Now Ready for the Labs that Use the Hardware Kit

If you have completed all eight prelabs (including this one) then you are now ready for the labs that use the hardware kit.

If something didn't work, consult a TA or Dr.&nbsp;Bohn for help.


> 📝 **Grading Note**
>
> To receive credit for Prelab 8, you will need to complete [the assignment on Canvas](https://mynu.instructure.com/courses/13509/assignments/1028633).


---

|               [⬅️](07-seven-segment.md)               |      [⬆️](../README.md)      |                         |
|:-----------------------------------------------------:|:----------------------------:|:-----------------------:|
| [Test the Seven-Segment Display](07-seven-segment.md) | [Front Matter](../README.md) |                         |
