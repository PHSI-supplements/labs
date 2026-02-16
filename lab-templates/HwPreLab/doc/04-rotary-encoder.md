## Test the Rotary Encoder

> ❗️ **Important**
>
> If you have not already completed Prelab 2, please complete Prelab 2 first!

In this pre-lab, you will confirm that the rotary encoder module is functioning, and you probably will discover a phenomenon of mechanical switches.

> 📝 **Grading Note**
>
> To receive credit for Prelab 4, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190106).


### Attach the Rotary Encoder Module to the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Hold the rotary encoder module next to the sockets on the left-side of the Cow Pi.
- [ ] Align the rotary encoder module's **A** pin with the Cow Pi's **GP17**, the rotary encoder module's **B** pin with the Cow Pi's **GP16**, and the rotary encoder module's **GND** pin with the **GND** socket adjacent to GP16.<br>
  <img src="images/rotary-encoder/line-up-rotary-encoder.png" width="300" alt="A rotary encoder module held next to the Cow Pi board with the A pin aligned with the GP17 socket, the B pin aligned with the GP16 socket, and the GND pin aligned to the adjacent GND pin.">
- [ ] Slide the rotary encoder's pins into the GP17, GP16, and GND sockets.<br>
  <img src="images/rotary-encoder/insert-rotary-encoder.png" width="300" alt="A rotary encoder module inserted into a Cow Pi's sockets.">


### Activate the Bootloader

Activating the bootloader requires a specific sequence of actions:

1. Press the RESET button, located between the white breadboard and the green Raspberry Pi Pico
2. While still pressing the RESET button, press the BOOTSEL button on the Raspberry Pi Pico
3. Release the RESET button
4. Release the BOOTSEL button

Drag & drop *prelab4.uf2* from the [build/](../build) directory into the mass storage device.


### What You Will See

The Cow Pi's display will show an arrow. As you turn the rotary encoder clockwise, the arrow will rotate clockwise. As you turn the rotary encoder counterclockwise, the arrow will rotate counterclockwise.

#### Switch Bounce

While the arrow will generally rotate as described, you will probably also see it "glitch" now and again.
It may jump back & forth between its original and new position;
it may rotate through a couple of positions and end up farther ahead than expected.
This is due to a phenomenon known as [switch bounce](https://en.wikipedia.org/wiki/Switch#Contact_bounce). 
The labs' starter code includes code to debounce mechanical switches, so you shouldn't see this problem during lab.

*Notice that the effects of switch bounce terminate within a few milliseconds, and you generally see only a few bounces.*
I point this out because some students will misattribute a logic error in their code as a switch bounce problem. 
When you work on the labs, and an input is read for as long as you're holding a button, or a quick tap of the button generates a few million inputs, then it is a logic error, not switch bounce.


### Prelab 4 Complete

If everything worked, you have finished Prelab 4.

If something didn't work, consult a TA or Dr.&nbsp;Bohn to double-check.

If the TA or Dr.&nbsp;Bohn confirms that the rotary encoder module doesn't work, visit Avery 27 to exchange it for another rotary encoder module.


### Disconnecting the Rotary Encoder Module from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Remove the rotary encoder module from the Cow Pi.


> 📝 **Grading Note**
>
> To receive credit for Prelab 4, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190106).


---

|          [⬅️](03-piezobuzzer.md)          |      [⬆️](../README.md)      |            [➡️](05-distance-sensor.md)            |
|:-----------------------------------------:|:----------------------------:|:-------------------------------------------------:|
| [Test the Piezobuzzer](03-piezobuzzer.md) | [Front Matter](../README.md) | [Test the Distance Sensor](05-distance-sensor.md) |
