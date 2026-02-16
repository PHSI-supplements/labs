## Compile a Program

> ❗️ **Important**
>
> If you have not already completed Prelab 2, please complete Prelab 2 first!

> 📝 **Grading Note**
>
> To receive credit for Prelab 8, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190110).


We will use PlatformIO to work with the Cow&bnsp;Pi development boards.

The PlatformIO developers recommend using the [VS Code plugin](https://platformio.org/install/ide?install=vscode), 
but there are [plugins for other IDEs](https://docs.platformio.org/en/latest/integration/ide/index.html), too, as well as a [command line interface toolset](https://platformio.org/install/cli). 
We have also pre-installed VS Code with the PlatformIO plugin on the lab computers in Avery 12, 15, 20, and 21.

You may want to take a quick look at the [parts of the PlatformIO Toolbar](https://docs.platformio.org/en/latest/integration/ide/vscode.html#platformio-toolbar).


### About PlatformIO and the Arduino Framework

PlatformIO is able to work with many frameworks; for the I/O labs, we will use the Arduino framework. As application programmers, the starting point is a program with two functions, setup() and loop(), along with any helper code that you need. PlatformIO will compile your program and link it to a main() function that looks something like:

```c
int main(void) {
    setup();
    while(true) {
        loop();
    }
}
```


### Obtain the Starter Code

If you have not already retrieved HwPreLab, review the "Retrieving the Lab" section in the README.md file at the root directory of your repository and the troubleshooting steps that it refers to. 
The Git commands to retrieve HwPreLab are:

```shell
git status
git fetch origin HwPreLab
git merge --ff origin/HwPreLab
```


### Load the Starter Code

These instructions assume you are using VS Code.

- Install the [PlatformIO plugin](https://platformio.org/install/ide?install=vscode).
  (Skip this step if you're using a lab computer.)
- Open VS Code (or whichever IDE you use).
- Open the PlatformIO Home.
  - You will see a bug head icon in VS Code's left-side menu; this is PlatformIO’s logo.
    <img src="images/PlatformIO/PlatformIO%20icon.png" height="50" alt="A screenshot of a stylized bug's head.">
  - Click on the PlatformIO logo.
  - After a few seconds, a PlatformIO side-window will appear.
    In that side-window, click on the "Select a Folder" or "Pick a Folder" button.
    - In other IDEs, you will use the "Open Project" button from the PlatformIO Home.
  - Navigate to the HwPreLab project's directory, and open the project (the directory with the *platformio.ini* file).
    - If the PlatformIO Home had not already started, wait for the PlatformIO Home to start.


### About the PlatformIO Toolbar

The PlatformIO Toolbar has a few options.
<img src="images/PlatformIO/PlatformIO%20toolbar.png" height="50" alt="A screenshot of a toolbar with several icons.">

- The house icon takes you to the PlatformIO Home
- The checkmark icon compiles your program
- ~~The arrow icon uploads your program to the Cow&nbsp;Pi~~ <font color="red">***we will not use the arrow icon this semester***</font>
- The trash can icon deletes your program’s compiled firmware
- The beaker icon runs unit tests
- The plug icon opens a Serial Monitor to interact with programs on the Cow Pi
- The box with an angle bracket opens a command-line terminal


### Compile the Program

Click on the PlatformIO Toolbar's checkmark icon to compile the program
- The first time that you compile a program for the Cow Pi, you will see several compilation messages as the various libraries are compiled for your program.
  These will include some warning messages due to a little sloppiness in the Arduino framework's code.
  You can safely ignore *these* warning messages.
  (You should always address warning messages that are from your own code.)

We have added a script to place a copy of the compiled program in the [build/](../build) directory, with the date and time of the compilation in the filename.

<!--
The script also automatically opens your system's file browser, pointing to the [build/](../build) directory. 
If you do not like this behavior, then edit *rename-uf2.py* to change

```python
open_file_browser = True
```

to

```python
open_file_browser = False
```
-->


### Activate the Bootloader

Activating the bootloader requires a specific sequence of actions:

1. Press the RESET button, located between the white breadboard and the green Raspberry Pi Pico
2. While still pressing the RESET button, press the BOOTSEL button on the Raspberry Pi Pico
3. Release the RESET button
4. Release the BOOTSEL button

Drag & drop *prelab8-yyyymmdd-hhmm.uf2* from the [build/](../build) directory into the mass storage device.


### What You Will See

The Cow&nbsp;Pi's display will show information about the tooling used to build the program.


### You Are Now Ready for th Labs that Use the Hardware Kit

If you have completed all eight prelabs (including this one) then you are now ready for the labs that use the hardware kit.

If something didn't work, consult a TA or Dr.&nbsp;Bohn for help.


> 📝 **Grading Note**
>
> To receive credit for Prelab 8, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190110).


### Optional, but Recommended

Because of USB driver issues on Windows systems (particularly Windows&nbsp;11), 
we have provided alternatives to printf debugging statements that make use of the Cow&nbsp;Pi's display.


#### Liveness Counter

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

You can see an example of the third case by pressing your Cow Pi's left pushbutton.


#### Display Debugging Strings

Open *prelab8.c* and look at the first if statement in the loop() function.
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

In the `if` path, add this line of code:
```c
display_string(7, "left position");
```
That is an example of displaying a string literal.
You can also use `sprintf()` to generate a string.
Notice that we have already created a buffer.
In the `else` path, add these lines of code:
```c
sprintf(buffer, "line %d", __LINE__);
display_string(7, buffer);
```
Compile the program and upload it to the Cow Pi.
Toggle the left switch back and forth to see the two different messages.


#### Counting Visits

Suppose that you want to know whether a path has been followed once or many times. 
We have provided another function
```c
void count_visits(int row)
```
that keeps track of the number of times it has been called for a particular row and displays that counter in the last two columns of that row.
For example, the liveness counter previously mentioned is a call to `count_visits(7)` at the end of the `loop()` function.

Change the display code in the `if` path to:
```c
display_string(5, "left position");
count_visits(5);
```
and in the `else` path:
```c
sprintf(buffer, "line %d", __LINE__);
display_string(6, buffer);
count_visits(6);
```
(Notice that we have changed the rows that these will be displayed on.)

Compile the program and upload it to the Cow Pi. 
Toggle the left switch back and forth to see the two new counters update accordingly.


#### The Display is Buffered

Now look at the second `if` statement, the one that checks whether the left button is pressed.
In that `if` block, before the `for (;;)` line, add this line of code:
```c
display_string(4, "stuck");
```
Compile the program and upload it to the Cow Pi.
After the program is running, press the left button.
Notice that the liveness counter stopped, but the "stuck" message wasn't displayed.

You may recall that on a regular computer system, the standard output is buffered, 
so `printf()` can be problematic when trying to localize code that crashes a program. 
You can overcome that by flushing the standard output with `fflush(stdout)` or by printing to `stderr` instead with `fprintf(stderr, ...)`.
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

Try each of those options and confirm for yourself that they will allow the "stuck" message to be displayed.


---

|               [⬅️](07-seven-segment.md)               |      [⬆️](../README.md)      |                         |
|:-----------------------------------------------------:|:----------------------------:|:-----------------------:|
| [Test the Seven-Segment Display](07-seven-segment.md) | [Front Matter](../README.md) |                         |
