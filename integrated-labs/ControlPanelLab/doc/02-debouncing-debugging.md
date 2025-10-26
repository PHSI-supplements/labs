## Debouncing and Debugging

### Debouncing

```
      ┏┓
      ┃┃╱╲ in
      ┃╱╱╲╲ this
      ╱╱╭╮╲╲ house
      ▔▏┗┛▕▔  we
      ╱▔▔▔▔▔▔▔▔▔▔╲
obey the laws of physics
     ╱╱ ┏┳┓╭╮┏┳┓ ╲╲
     ▔▏ ┗┻┛┃┃┗┻┛ ▕▔
```

Mechanical buttons and switches demonstrate a phenomenon called *switch bounce*.
This causes voltage to fluctuate for hundreds, often thousands, of microseconds when the contacts close or open.
When this fluctuation is in the indeterminate region between the logical low and high thresholds, it can cause the logic level to "bounce" back-and-forth between high and low until settling into the final, correct logic level.
This causes the digital circuitry or software to "see" multiple triggering events.

You probably saw an example of this in the prelab.

A traditional way to debounce is to introduce a simple low-pass filter using a resistor and a capacitor.
Other common hardware-based approaches use digital feedback circuits.
Hardware design can be simplified, and manufacturing cost can be reduced, by solving a hardware problem with software.
This, of course, transfers the design complexity to the software.

The CowPi library includes the `cowpi_debounce_byte()`, `cowpi_debounce_short()`, and `cowpi_debounce_long()`  functions that essentially implement a low-pass filter in software.
The functions in *io_functions.c* make use of `cowpi_debounce_byte()` and `cowpi_debounce_long()`.
When you modify these functions, as long as you preserve those `cowpi_debounce_byte()` calls, you do not need to worry further about debouncing.


### Debugging

You can send short debug messages to the Cow&nbsp;Pi's display, as you saw in the prelab.
The display module can display up to 8 rows of text, 16 characters per row;
however, the assignment only makes use of rows&nbsp;0 \& 1.
This leaves rows&nbsp;2--7 available for short (16 character) debug messages.
You might find `count_visits`, declared in *display.h*, to be useful.


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |             [➡️](03-labtime.md)              |
|:----------------------------------------:|:----------------------------:|:--------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Initial Changes to the Code](03-labtime.md) |
