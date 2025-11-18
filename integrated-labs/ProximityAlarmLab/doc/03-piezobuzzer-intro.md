## Generating Tones with a Piezobuzzer

### Theory of Operation

Piezoelectric crystals have a property that causes them to turn mechanical energy into electrical energy, and vice-versa.
We will apply electricity to the crystal inside the buzzer to cause a thin plate to deform, and then remove the electricity to allow the plate to relax.
By repeatedly doing this, we will cause the piezobuzzer to produce sound.

Specifically, we want a 1kHz tone.
This means that the audio wave must reach its peak 1,000 times per second.
Put another way, during every second there must be 1,000 peaks -- dividing that out, we see that there must be 500μs between the wave's peaks.


### Practical Considerations

The piezobuzzers have enough internal resistance that we can safely drive the crystal directly from a microcontroller pin.

As we will be driving the piezobuzzer with a digital output pin, we cannot produce a pure sine wave;
instead we will produce a square wave.
Because it will be a square wave, in addition to the 1kHz tone, there will also be harmonics at 3kHz, 5kHz, 7kHz, etc.
We will not attempt to suppress the harmonics.
To produce the exact 1kHz square wave, you need to use a timer interrupt.
At first glance, you might think to generate an interrupt every 1000μs;
however, the wave needs to have a peak and a trough every 1000μs.
(Without troughs, there are no peaks.)
Therefore, you want to generate an interrupt every 500μs, alternatingly setting the `BUZZER_PIN` pin logic-high and logic-low.


### Register a Timer Interrupt Service Routine

- [ ] Locate the `initialize_alarm()` function in *alarm.c*.
- [ ] At the end of the function, use the `register_periodic_timer_ISR()` function to configure a timer interrupt and to register the ISR to be called when the interrupt fires.
  - The timer number to use is `ALARM_TIMER`.
  - The ISR is `handle_alarm_timer`.

---

|              [⬅️](02-interrupts.md)               |      [⬆️](../README.md)      |         [➡️](04-alarm.md)          |
|:-------------------------------------------------:|:----------------------------:|:----------------------------------:|
| [Interrupt-Driven Input/Output](02-interrupts.md) | [Front Matter](../README.md) | [Generating an Alarm](04-alarm.md) |
