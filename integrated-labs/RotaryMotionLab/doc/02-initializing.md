## Setting up the Timer and the I/O Port Pointer

There is a named constant, `PULSE_INCREMENT_uS` whose value is 100.
We will explain its significance shortly;
for now, use it as a timer interrupt period.

- [ ] In *timer.c*, add code to `initialize_timer()` to configure a timer interrupt and to register the ISR to be called when the interrupt fires.
  - The timer number to use is 0.
  - The interrupt period is 100µs; that is, `PULSE_INCREMENT_uS`. 
  - The ISR is `handle_timer_interrupt`.
  > 💡 **Tip**
  >
  > If you don't remember how to configure a timer interrupt and to register its ISR, review your work from ProximityAlarmLab.

You will also have a couple of functions to write that use memory-mapped I/O.

- [ ] In *io_functions.c*, modify the last line in `initialize_io` to set the address that `ioport` points to,
  so that it points to the base address of the memory-mapped I/O registers used to read from and write to peripherals connected to the microcontroller's I/O pins.
  > 💡 **Tip**
  >
  > If you don't remember how to set the correct address, review your work from ControlPanelLab.


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                      [➡️](03-servo-theory.md)                       |
|:----------------------------------------:|:----------------------------:|:-------------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Controlling a Servomotor: Theory of Operation](03-servo-theory.md) |
