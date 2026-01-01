## Interrupt-Driven Input/Output

### A Different but Familiar Programming Paradigm

In CalculatorLab you used polling to determine when there is a change on an input pin and to know when a certain amount of time has passed. 
In this lab, you will rely on interrupts to let your code know when there is a change on an input pin,
and you will rely on interrupts to let your code know when a certain amount of time has passed.
Most of the code you wrote in the earlier lab assignments for this course used imperative programming: 
you, the programmer, had full control over changes to the program state. 
In CalculatorLab, you stretched this model to something resembling shared-memory concurrent programming: 
you still had full control over changes to the program state of your program's flow of control, 
but your program periodically read variables (memory-mapped input registers) that could be changed by another flow of control (the physical world).
In this lab assignment, you will write code that reacts to things happening in the physical world;
your code program state will not change except in reaction to interrupts.
Conceptually, this isn’t very different from event-driven programming that you learned in CSCE 156, RAIK 184H, or SOFT 161. 
While configuring the hardware timer is a little more complex than configuring a GUI framework’s timer, 
handling a timer interrupt is very much like writing an `onTimeout()` event handler.
Similarly, handling a change on an input pin is very much like writing an `onMouseClick()` event handler. 
Your code is not focused on when the button is pressed or released, nor even on detecting that a button has been pressed or released;
it is focused solely on what should happen when the button is pressed or released.


### Keep Interrupt Service Routines Short

You want your program to spend as little time as possible in an ISR.
The admonition to keep ISRs short doesn't strictly mean to write as few lines of code as possible:
it means to have as few lines execute as possible.
For example, a lengthy `switch` statement in which each case has only a few lines of code is still "short".
The admonition also doesn't *just* mean to write as few lines as possible:
the lines that you write must also be fast.
Some functions such as `sprintf()`, `refresh_display()`, and `count_visits()` are particularly long-running and should not be called inside an ISR.
A call to `display_string()` with a string literal might be okay.
If you need to send information to the user, it would be better to set a variable, and to have code that is in the main control loop use that variable to send information to the user.


### Registering Interrupt Service Routines

The `register_periodic_timer_ISR()` function configures a timer interrupt and registers the ISR to be called when the interrupt fires.
- The first argument is the timer number.
- The second argument is the interrupt period in microseconds.
- The third argument is the name of the function that will handle the interrupt (*only* the name -- do not include the parentheses).

The `register_pin_ISR()` configures an interrupt to fire whenever the value on an input pin changes (both low-to-high and high-to-low) and registers the ISR to be called when the interrupt fires.
- The first argument is a mask to indicate which pin(s) will trigger the interrupt, such as `1 << PIN_NUMBER`.
- The second argument is the name of the function that will handle the interrupt (*only* the name -- do not include the parentheses).


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                 [➡️](03-piezobuzzer-intro.md)                  |
|:----------------------------------------:|:----------------------------:|:--------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Generating Tones with a Piezobuzzer](03-piezobuzzer-intro.md) |
