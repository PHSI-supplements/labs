## Appendix B: Attaching and Detaching Peripheral Devices

### Attach the Piezobuzzer Module to the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Hold the piezobuzzer module next to the sockets on the left-side of the Cow Pi.
  Align the piezobuzzer module's **TONE** pin with the Cow Pi's **GP22**, and the piezobuzzer module's **GND** pin with the **GND** socket adjacent to GP22.
  <br><img src="images/piezobuzzer_module/line-up-piezo.png" width="300" alt="A piezobuzzer module held next to the Cow Pi board with the TONE pin aligned with the GP22 socket and the GND pin aligned to the adjacent GND pin.">
- [ ] Slide the piezobuzzer module's TONE and GND pins into the GP22 and GND sockets.
  <br><img src="images/piezobuzzer_module/insert-piezo.png" width="300" alt="A piezobuzzer module inserted into a Cow Pi's sockets.">

### Disconnecting the Piezobuzzer Module from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Remove the piezobuzzer from the Cow Pi.

---

### Attach the Distance Sensor to its Adapter

*If your distance sensor is already attached to its adapter, you can skip this step.*

Observe that the distance sensor has four pins.
The adapter has a socket designed to receive four pins.
Next to this socket is a stylized representation of the distance sensor with its two acoustic shrouds.
<br><img src="images/distance_sensor_module/distance-sensor-and-adapter.png" width="300" alt="A small printed circuit board next to a slightly larger circuit board. The larger board has two aluminum cylinders with grates at the end, and a smaller stadium-shaped component in between.">
Insert the sensor's four pins into the 4-hole socket in the orientation indicated by the diagram on the adapter.
<br><img src="images/distance_sensor_module/distance-sensor-attached-to-adapter.png" width="300" alt="A small circuit board with assorted integrated circuits inserted into a socket on a smaller circuit board.">

### Attach the Distance Sensor Module to the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] The adapter has a second socket, labeled **PWR**.
  <br><img src="images/distance_sensor_module/identify-power-socket.jpg" width="300" alt="A small circuit board with a PWR socket. The end of a wire is next to the circuit board.">
  <br>Insert one end of a jumper wire into the PWR socket.
  <br><img src="images/distance_sensor_module/insert-wire-into-power-socket.jpg" width="300" alt="A small circuit board with a wire inserted into a socket.">
- [ ] Hold the distance sensor module next to the sockets on the left-side of the Cow Pi, aligning the adapter's **TRIG** pin with the Cow Pi's **GP17**, the adapter's **ECHO** pin with the Cow Pi's **GP16**, and the adapter's **GND** pin with the **GND** socket adjacent to GP16.
  <br><img src="images/distance_sensor_module/line-up-sensor-adapter-with-cowpi.jpg" width="300" alt="A small circuit board with three pins being held next to a larger, red circuit board.">
- [ ] Slide the distance sensor adapter's pins into the GP17, GP16, and GND sockets.
  <br><img src="images/distance_sensor_module/adapter-connected-to-cowpi.jpg" width="300" alt="A small circuit board mated to a larger circuit board.">
- [ ] The left side of the Cow Pi has two sockets labeled **5V**.
  <br><img src="images/distance_sensor_module/line-up-wire-with-5v.jpg" width="300" alt="The end of a wire being held next to a socket labeled 5V.">
- [ ] Insert the other end of the jumper wire into one of the 5V sockets.
  <br><img src="images/distance_sensor_module/distance-sensor-fully-connected.jpg" width="300" alt="A blue circuit board with assorted integrated circuits mounted on a small green circuit board. The small green circuit board is mated to a larger red circuit board. There is also a wire running from the small green circuit board to the larger red circuit board.">

### Disconnecting the Distance Sensor Module from the Cow Pi

- [ ] Disconnect the Cow Pi from your computer.
- [ ] Disconnect the distance sensor's power wire from the Cow Pi.
- [ ] Remove the piezobuzzer from the Cow Pi.
- [ ] Optionally, disconnect the power wire from the adapter.


---

|            [⬅️](AA-checkoff.md)            |      [⬆️](../README.md)      |                                       [➡️](CC-distance-formulation.md)                                       |
|:------------------------------------------:|:----------------------------:|:------------------------------------------------------------------------------------------------------------:|
| [Appendix A: Lab Checkoff](AA-checkoff.md) | [Front Matter](../README.md) | [Appendix C: Re-Expressing the Distance Equation to use only Integer Arithmetic](CC-distance-formulation.md) |
