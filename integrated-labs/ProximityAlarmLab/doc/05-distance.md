## Measuring the Distance to an Object

You will use the ultrasonic echo sensor to determine the distance to an object.

### Theory of Operation

The ultrasonic echo sensor has a simple interface.
If your program places a logic-high signal on the `TRIGGER_PIN` pin for 10µs and then drop it to logic-low, then the device will emit a short burst of ultrasound.
The device will then raise the `ECHO_PIN` pin's logic level to high.
If there is a nearby object, the ultrasound will reflect off of it, and the sensor will detect the echo.
After detecting the echo, the device will drop the `ECHO_PIN` pin's logic level to low.
If no echo is received, then the device will eventually time-out and drop the `ECHO_PIN` pin's logic level to low.
After affording the device a quiescent period, the cycle can be repeated.

<!--
%Various datasheets\footnote{
%    [https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)}$^,$\footnote{[https://web.eece.maine.edu/&nbsp;zhu/book/lab/HC-SR04\%20User\%20Manual.pdf](https://web.eece.maine.edu/&nbsp;zhu/book/lab/HC-SR04\%20User\%20Manual.pdf)}$^,$\footnote{[https://www.handsontec.com/dataspecs/HC-SR04-Ultrasonic.pdf](https://www.handsontec.com/dataspecs/HC-SR04-Ultrasonic.pdf)
%}\ differ slightly in a few particulars.
%Some describe the time-out period as 36ms, others 38ms.
%Some describe the quiescent period as at least 10ms after the `ECHO_PIN` pin's logic drops low; others recommend at least 60ms after the `ECHO_PIN` pin's logic goes high.
%The datasheets generally agree that under typical conditions, the device will be able to detect an echo from a $0.5\mathrm{m}^2$ target within 4&nbsp;meters of the sensor.
%One datasheet suggests that under some conditions, this distance may be as great as 5&nbsp;meters.\footnote{
%    During testing of the sample solution, sometimes objects 250cm away couldn't always be reliably detected; at other times I was able to detect objects up to 320cm away.
%}
-->

If your program measures the time between the `ECHO_PIN` pin's logic going high and subsequently going low, then it knows how long the ultrasound travelled to the object and back again.
The classical relationship $distance = speed \times time$ requires that we know how fast the ultrasound travels.

The speed of sound depends on the medium it travels through and the temperature of that medium.
We will assume the medium is air.

The speed of sound is a function air temperature.
Assuming the temperature $T$ is measured in ºC, the speed of sound in air is[^1]
$$331.228 \times \sqrt{1 + \frac{T}{273.15}} \frac{m}{s}$$

[^1]: [https://www.weather.gov/media/epz/wxcalc/speedOfSound.pdf](https://www.weather.gov/media/epz/wxcalc/speedOfSound.pdf)

Thus, by knowing the round-trip travel time, we can determine the distance that the ultrasonic pulse travelled.
The distance to the object it echoed off of will be half of the round-trip distance.


### The Wrong Calculation

The internet is littered with example code for measuring distance that instructs you to divide the ultrasonic pulse's round-trip travel time by 58 to obtain the distance in centimeters.
Like approximating gravitational acceleration as $10\frac{m}{s^2}$, the calculation of "divide microseconds by 58" is simple enough for someone to easily use and provides an adequate approximation.
Like approximating gravitational acceleration as $10\frac{m}{s^2}$, the calculation of "divide microseconds by 58" provides you with the wrong answer if "approximately correct" is insufficient.

The "divide microseconds by 58" approximation assumes the speed of sound is $\frac{1}{29}\frac{cm}{\mu s}$, or approximately $344.83\frac{m}{s}$.
A little algebra will tell you that is is the speed of sound when the air temperature is 22.8ºC (73.2ºF).


### The Correct Calculation

The distance to a detected object is half of the ultrasonic pulse's round-trip distance.
Using the speed of sound equation from above, we can accurately find the distance to an object:

$$distance_{cm} = \frac{time_{\mu s}}{2} \times \left( 331.228 \times \sqrt{1 + \frac{T_{^oc}}{273.15}} \frac{m}{s} \right) \times \frac{s}{1,000,000\mu s} \times \frac{100cm}{m}$$


#### Practical Consideration: Arithmetic

As our microcontroller does not have a floating point unit (FPU), we want to avoid floating point calculations, which are computationally expensive when performed entirely in software.
The RP2040 has an integer divider that requires 8 processor clock cycles to perform division, so we might allow integer division with the new hardware -- but won't have to.
The equation we'll use not only avoid floating point arithmetic, it also (if you are able to recall Chapter 3 material) does not require integer division.

#### Practical Consideration: Temperature

The RP2040 has a five-channel analog-to-digital converter (ADC).
Three of those channels are connected to input pins (which can be accessed through the socket panel on the bottom edge of the Cow&nbsp;Pi).
The fourth is used to monitor the power delivered to the microcontroller.
The fifth measures the voltage drop across a diode, which varies with temperature.

The RP2040 datasheet includes an equation to convert the value found in the ADC's memory-mapped register into the voltage drop,
and it includes an equation to convert the voltage drop into the temperature.
The equation we'll use incorporates these conversions, so you will only need the value found in the ADC's register.

(The starter code includes a function to convert the ADC's register value to the temperature in Celsius in case you are curious, but you will not need that function to complete this assignment.)

#### The Equation

The equation we'll use that accurately computes the distance is:

$$distance_{cm} = time_{\mu s} \times \left( 256,108,888 - 121,907 \times ADC\_register\_value \right) \frac{cm}{\mu s} \div 2^{33}$$

The derivation of these equation can be found in this assignment's [Appendix C](CC-distance-formulation.md).

> ⓘ **Note**
> 
> Even though $distance$ will be less than 500cm, you will need at least 44 bits to represent the intermediate products when performing the arithmetic.

> ❗️ **Important**
> 
> Use the `LL` suffix with the integer literals in that equation to force them to be treated as 64-bit `long long` integers.

<!--
%There is also a practical consideration with respect to the sensor itself.
%Sound isn't particularly directional.
%The horns surrounding the ultrasonic transducers help to limit the "beam width," but only to a degree.
%Pointing the sensor straight down an otherwise empty hallway, you will probably still detect a reflection from the walls to either side.\footnote{
%    If you're feeling nerdy, you could use right-angle trigonometry to determine the "beam width" --
%    point the sensor straight at a wall to determine how far away from it you are (the "opposite"), then point the sensor parallel to the wall and take a reading (the hypoteneuse).
%    Divide the "opposite" by the hypoteneuse and take the arcsin -- the resulting value is the angle from straigth-ahead to how far to the right/left the sensor will detect a reflection.
%}
-->


### The Distance Sensor State Machine

We will control the distance sensor using a state machine:

![A diagram depicting a state machine that can be used to control the distance sensor](images/range_finder/sensorStateMachine.png)

> ⓘ **Note**
>
> The diagram shows some transitions caused by "timer overflow".
> This is because when we used a different microcontroller, we used interrupts generated when a 16-bit timer overflowed.
> Wherever you see "timer overflow" in the diagram, you should read that is "timer interrupt".

Both the input state machines and the alarm state machine had all of their state transitions contained within a single function.
The state machine for the distance sensor will have some transitions in the ISR for a timer interrupt and some transitions in the ISR for a pin interrupt, as well as and some state actions in functions that are run by the program's main control loop.

We have found that 32,768µs is a good timer interrupt period for the distance sensor's state machine:
- That is longer than the round-trip time of the sensor's advertised maximum range (500cm) and definitely longer than its effective maximum range (350cm-400cm), so we are sure that any object that can be detected will be detected before the timer interrupt (see the `Active-Detected` state).
- That is shorter than the time after which the sensor will time out (about 36ms), so we are sure that when there isn't an object to be detected, the pulse's trailing edge due to time-out will occur after the state machine transitions from `Active-Listening` to `Quiescent`.
- That provides an ample quiescent period.
- (Not relevant to the RP2040, but it's also the time after which a 16-bit timer will overflow if it "ticks" every ½µs.)


### Register a Timer Interrupt Service Routine and a Pin Interrupt Service Routine

- [ ] Locate the `initialize_sensor()` function in *sensor.c*.
- [ ] At the end of the function, use the `register_periodic_timer_ISR()` function to configure a timer interrupt and to register the ISR to be called when the interrupt fires.
  - The timer number to use is `SENSOR_TIMER`.
  - The ISR is `handle_sensor_timer`.
- [ ] At the end of the function, use the `register_pin_ISR()` function to configure an interrupt to fire when the value on a pin changes and to register the ISR to be called when the interrupt fires.
  - The pin is `ECHO_PIN`.
  - The ISR is `on_pulse_edge`.


---

|         [⬅️](04-alarm.md)         |      [⬆️](../README.md)      |                 [➡️](06-sensor-state-machine.md)                  |
|:---------------------------------:|:----------------------------:|:-----------------------------------------------------------------:|
| [Polling Discussion](04-alarm.md) | [Front Matter](../README.md) | [Building the Sensor's State Machine](06-sensor-state-machine.md) |
