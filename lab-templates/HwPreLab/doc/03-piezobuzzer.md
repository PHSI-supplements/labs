## Test the Piezobuzzer

> ❗️ **Important**
> 
> If you have not already completed Prelab 2, please complete Prelab 2 first!

In this pre-lab, you will learn how to connect an unpowered peripheral to the Cow Pi, and you will confirm that the piezobuzzer module is functioning.

> 📝 **Grading Note**
>
> To receive credit for Prelab 3, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190105).


### Attach the Piezobuzzer Module to the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Hold the piezobuzzer module next to the sockets on the left-side of the Cow Pi.
  Align the piezobuzzer module's **TONE** pin with the Cow Pi's **GP22**, and the piezobuzzer module's **GND** pin with the **GND** socket adjacent to GP22.<br>
  <img src="images/piezobuzzer_module/line-up-piezo.png" width="300" alt="A piezobuzzer module held next to the Cow Pi board with the TONE pin aligned with the GP22 socket and the GND pin aligned to the adjacent GND pin.">
- [ ] Slide the piezobuzzer module's TONE and GND pins into the GP22 and GND sockets.<br>
  <img src="images/piezobuzzer_module/insert-piezo.png" width="300" alt="A piezobuzzer module inserted into a Cow Pi's sockets.">


### Activate the Bootloader

Activating the bootloader requires a specific sequence of actions:

1. Press the RESET button, located between the white breadboard and the green Raspberry Pi Pico
2. While still pressing the RESET button, press the BOOTSEL button on the Raspberry Pi Pico
3. Release the RESET button
4. Release the BOOTSEL button

Drag & drop *prelab3.uf2* from the [build/](../build) directory into the mass storage device.


### What You Will Hear

The Cow&nbsp;Pi will play a tinny rendition of a recognizable tune.


### Prelab 3 Complete

If everything worked, you have finished Prelab 3.

If something didn't work, consult a TA or Dr.&nbsp;Bohn to double-check.

If the TA or Dr.&nbsp;Bohn confirms that the piezobuzzer module doesn't work, visit Avery 27 to exchange it for another piezobuzzer module.


### Disconnecting the Piezobuzzer Module from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Remove the piezobuzzer from the Cow Pi.


> 📝 **Grading Note**
>
> To receive credit for Prelab 3, you will need to complete [the assignment on Canvas](https://canvas.unl.edu/courses/209782/assignments/2190105).


---

|           [⬅️](02-control-panel.md)           |      [⬆️](../README.md)      |           [➡️](04-rotary-encoder.md)            |
|:---------------------------------------------:|:----------------------------:|:-----------------------------------------------:|
| [Test the Control Panel](02-control-panel.md) | [Front Matter](../README.md) | [Test the Rotary Encoder](04-rotary-encoder.md) |
