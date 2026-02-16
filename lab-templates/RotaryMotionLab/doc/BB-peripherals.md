## Appendix B: Attaching and Detaching Peripheral Devices

### Attach the Servo Arm to the Servomotor 

*If your servomotor already has a servo arm attached, you can skip this step.*

- The servo consists of a nylon arm and a servomotor.
- [ ] Take one of the servo arms (for our purposes, it doesn't matter which one) and hold it over the servomotor's shaft (for our purposes, the axial orientation doesn't matter).
  One end of the arm's axis has toothed ridges to interconnect with the servomotor's shaft; 
  that end should be pointed toward the shaft.
  <br><img src="images/servo/aboutToAttachServoArm.jpg" width="300" alt="A servo arm being held over a servomotor's shaft.">
- Press the arm onto the shaft.
  <br><img src="images/servo/servoArmAttached.jpg" width="300" alt="A servo. The servo arm has been placed on the servomotor's shaft.">

We recommend that you do not use a screw to hold the servo arm to the servomotor. If you do use a screw, do not fully tighten it.

### Attach the Servo to its Adapter

*If your servo is already attached to its adapter, you can skip this step.*

- Observe that the servo's cable is designed to connect to three pins. 
- The adapter has three pins on the end labeled ***Servo*** and two pins on the end labeled ***µC*** ("microcontroller").
- [ ] Connect the servo's cable to the *Servo* end of the adapter, such that the **brown** wire is connected to the **GND** pin, and the **yellow** wire is connected to the **PWM** pin.
  <br><img src="images/servo/servo-cable-and-adapter.png" width="300" alt="A 3-wire cable with brown, red, and yellow wires is connected to a small white circuit board. The brown wire lines up with the GND label; the red wire lines up with the PWR label; and the yellow wire lines up with the PWM label.">

### Attach the Servo to the Cow Pi

Disconnect the Cow Pi from your computer.
After your Cow Pi is no longer powered-up:

- [ ] The adapter has a **PWR** socket.
  Insert one end of a jumper wire into the PWR socket.
- [ ] Hold the servo cable's adapter next to the sockets on the left-side of the Cow Pi, aligning the adapter's **PWM** pin with the Cow Pi's **GP22**, and the adapter's **GND** pin with the **GND** socket adjacent to GP22.such that the **brown** wire is connected to the **GND** pin, and the **yellow** wire is connected to the **PWM** pin.
  <br><img src="images/servo/servo-adapter-next-to-sockets.jpg" width="300" alt="A small green circuit board held next to a larger red circuit board. One of the green circuit board's pins is lined up with the red's 'GND' label, and the other pin is lined up with 'GP22'">
- [ ] Slide the servo cable adapter's pins into the GP22 and GND sockets.
  Insert the other end of the jumper wire into a 5V socket.such that the **brown** wire is connected to the **GND** pin, and the **yellow** wire is connected to the **PWM** pin.
  <br><img src="images/servo/servo-adapter-inserted.jpg" width="300" alt="A small green circuit board mated to a larger red circuit board. There is also a wire running between the two boards.">

<!--
  ![A servo arm being held over a servomotor's shaft.](images/servo/aboutToAttachServoArm.jpg)
  ![A servo. The servo arm has been placed on the servomotor's shaft.](images/servo/servoArmAttached.jpg)
  ![A 3-wire cable with brown, red, and yellow wires is connected to a small white circuit board. The brown wire lines up with the GND label; the red wire lines up with the PWR label; and the yellow wire lines up with the PWM label.](images/servo/servo-cable-and-adapter.png)
  ![A small green circuit board held next to a larger red circuit board. one of the green circuit board's pins is lined up with the red's "GND" label, and the other pin is lined up with "GP22".](images/servo/servo-adapter-next-to-sockets.jpg)
  ![A small green circuit board mated to a larger red circuit board. There is also a wire running between the two boards.](images/servo/servo-adapter-inserted.jpg)
-->

### Disconnecting the Servo from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Disconnect the servo adapter's power wire from the Cow Pi.
- [ ] Remove the servo adapter from the Cow Pi.
  - We recommend that you leave the servo connected to its adapter.
- [ ] Optionally, disconnect the power wire from the servo adapter.


---


### Attach the Rotary Encoder Module to the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Hold the rotary encoder module next to the sockets on the left-side of the Cow Pi.
- [ ] Align the rotary encoder module's **A** pin with the Cow Pi's **GP17**, the rotary encoder module's **B** pin with the Cow Pi's **GP16**, and the rotary encoder module's **GND** pin with the **GND** socket adjacent to GP16.
  <br><img src="images/rotary-encoder/line-up-rotary-encoder.png" width="300" alt="A rotary encoder module held next to the Cow Pi board with the A pin aligned with the GP17 socket, the B pin aligned with the GP16 socket, and the GND pin aligned to the adjacent GND pin.">
- [ ] Slide the rotary encoder's pins into the GP17, GP16, and GND sockets.
  <br><img src="images/rotary-encoder/insert-rotary-encoder.png" width="300" alt="A rotary encoder module inserted into a Cow Pi's sockets.">

<!--
![A rotary encoder module held next to the Cow Pi board with the A pin aligned with the GP17 socket, the B pin aligned with the GP16 socket, and the GND pin aligned to the adjacent GND pin.](images/rotary-encoder/line-up-rotary-encoder.png)
![A rotary encoder module inserted into a Cow Pi's sockets.](images/rotary-encoder/insert-rotary-encoder.png)
-->

### Disconnecting the Rotary Encoder Module from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Remove the rotary encoder module from the Cow Pi.


---

|            [⬅️](AA-checkoff.md)            |      [⬆️](../README.md)      |                            |
|:------------------------------------------:|:----------------------------:|:--------------------------:|
| [Appendix A: Lab Checkoff](AA-checkoff.md) | [Front Matter](../README.md) |                            |

