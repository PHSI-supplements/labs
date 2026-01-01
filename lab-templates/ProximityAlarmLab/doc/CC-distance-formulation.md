## Re-Expressing the Distance Equation to use only Integer Arithmetic

### Calculating the Speed of Sound

The speed of sound in air is[^2]
$$speed = 331.228 \times \sqrt{1 + \frac{T_{^oc}}{273.15}} \frac{m}{s} = 0.0331228 \times \sqrt{1 + \frac{T_{^oc}}{273.15}} \frac{cm}{\mu s}$$

[^2]: [https://www.weather.gov/media/epz/wxcalc/speedOfSound.pdf](https://www.weather.gov/media/epz/wxcalc/speedOfSound.pdf)

The presence of that square root would seem to be an obstacle to our goal of avoiding floating point calculations;
however, the expression's Taylor series gives us

$$speed             = 0.0331228 \times \left( 1 + \frac{T_{^oc}}{546.30} \right) \frac{cm}{\mu s}       $$
$$\phantom{xxxxxx}  = 0.0331228 \times \left( \frac{546.30 + T_{^oc}}{546.30} \right) \frac{cm}{\mu s}  $$
$$                  = \frac{546.30 + T_{^oc}}{16493.17} \frac{cm}{\mu s}                                $$



### Calculating the Temperature

The RP2040 has a temperature sensor connected to one of its analog-digital converter (ADC) inputs.
Section&nbsp;4.9.5 of the RP2040 datasheet[^3] shows that the temperature, in ºC, is:
$$T = 27 - \frac{ADC\_voltage - 0.706}{0.001721}$$

[^3]: [https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

The ADC is a 12-bit ADC with a reference voltage of 3.3V, and so

$$T_{^oc}                           = 27 - \frac{\frac{3.3 \times ADC\_register\_value}{2^{12}} - 0.706}{0.001721}                                                  $$
$$\phantom{xxxxxxxxxxxx}            = 27 - \frac{3.3 \times ADC\_register\_value - 0.706 \times 2^{12}}{0.001721 \times 2^{12}}                                     $$
$$\phantom{xxxxxxxxxxxxxxxxxxxxxxx} = \frac{0.046467 \times 2^{12} - \left( 3.3 \times ADC\_register\_value - 0.706 \times 2^{12} \right)}{0.001721 \times 2^{12}}  $$
$$\phantom{xxxxxxxxxxx}             = \frac{0.752467 \times 2^{12} - 3.3 \times ADC\_register\_value}{0.001721 \times 2^{12}}                                       $$
$$\phantom{xxxxxxxxxxxxxx}          \approx \frac{3.3 \times 0.22802 \times 2^{12} - 3.3 \times ADC\_register\_value}{0.001721 \times 2^{12}}                       $$
$$\phantom{xxxxxx}                  \approx \frac{0.22802 \times 2^{12} - ADC\_register\_value}{0.0005215 \times 2^{12}}                                            $$



### Calculating the Distance

Substituting the expression for the temperature into the expression for the speed of sound, we get:

$$speed                                 = \frac{546.30 + \frac{0.22802 \times 2^{12} - ADC\_register\_value}{0.0005215 \times 2^{12}}}{16493.17} \frac{cm}{\mu s}                                       $$
$$\phantom{xxxxxxxxxxxxxxxxxxxxxxxxxx}  = \frac{546.30 \times 0.0005215 \times 2^{12} + 0.22802 \times 2^{12} - ADC\_register\_value}{16493.17 \times 0.0005215 \times 2^{12}} \frac{cm}{\mu s}         $$
$$\phantom{xxxx}                        = \frac{0.5129 \times 2^{12} - ADC\_register\_value}{8.601438 \times 2^{12}} \frac{cm}{\mu s}                                                                   $$
$$\phantom{xxxx}                        \approx \left(0.05963 - \frac{ADC\_register\_value}{8.601438 \times 2^{12}} \right) \frac{cm}{\mu s}                                                            $$
$$\phantom{xxxxxxxxxxxxxx}              = \left(0.05963 \times \frac{2^{32}}{2^{32}}    -    \frac{ADC\_register\_value}{8.601438 \times 2^{12}} \times \frac{2^{20}}{2^{20}} \right) \frac{cm}{\mu s}  $$
$$\phantom{xxxxxxxxxxxxxxxx}            \approx \left( \frac{256,108,888}{2^{32}} - \frac{121,907 \times ADC\_register\_value}{2^{32}} \right) \frac{cm}{\mu s}                                         $$
$$\phantom{xxxxxxxxxxxx}                = \frac{256,108,888 - 121,907 \times ADC\_register\_value}{2^{32}} \frac{cm}{\mu s}                                                                             $$


The distance to an object, being half of the round-trip distance, is

$$distance      = \frac{1}{2} \times time_{\mu s} \times \frac{256,108,888 - 121,907 \times ADC\_register\_value}{2^{32}} \frac{cm}{\mu s}  $$
$$\phantom{xxx} = time_{\mu s} \times  \frac{256,108,888 - 121,907 \times ADC\_register\_value}{2^{33}} \frac{cm}{\mu s}                    $$

Recalling that division by a power-of-two can be replaced with a right-shift, this equation for distance requires no floating point arithmetic, nor does it require integer division.
The only (below-the-hood) complication is that the arithmetic will have to be performed using 64-bit integer types, and the RP2040 has a 32-bit word.

### Assembly Code for RP2040

```asm
compute_distance:
        // time in r0, ADC_register_value in r1
        push    {r4, r5, r6, lr}
        mov     ip, r0
        movs    r2, r1
        movs    r3, #0
        // 121,907 × ADC_register_value
        lsrs    r5, r1, #29
        lsls    r4, r1, #3
        subs    r4, r4, r2
        sbcs    r5, r5, r3
        lsrs    r6, r4, #23
        lsls    r1, r5, #9
        adds    r1, r6, r1
        lsls    r0, r4, #9
        adds    r0, r0, r2
        adcs    r1, r1, r3
        adds    r0, r0, r0
        adcs    r1, r1, r1
        adds    r0, r0, r2
        adcs    r1, r1, r3
        lsrs    r3, r0, #28
        lsls    r5, r1, #4
        adds    r5, r3, r5
        lsls    r4, r0, #4
        adds    r0, r0, r4
        adcs    r1, r1, r5
        // 256,108,888 - (121,907 × ADC_register_value)
        ldr     r4, .L2         // 2 clock cycles for load from SRAM
        movs    r5, #0
        subs    r4, r4, r0
        sbcs    r5, r5, r1
        movs    r0, r4
        movs    r1, r5
        mov     r2, ip
        movs    r3, #0
        // time × (256,108,888 - (121,907 × ADC_register_value))
        bl      __aeabi_lmul    // 30-50 clock cycles for 64-bit multiplication
        // time × (256,108,888 - (121,907 × ADC_register_value)) ÷ 2^{33}
        lsrs    r0, r1, #1
        // distance in r0
        pop     {r4, r5, r6, pc}
.L2:
        .word   256108888
```


---

|                           [⬅️](BB-peripherals.md)                           |      [⬆️](../README.md)      |                            |
|:---------------------------------------------------------------------------:|:----------------------------:|:--------------------------:|
| [Appendix B: Attaching and Detaching Peripheral Devices](BB-peripherals.md) | [Front Matter](../README.md) |                            |
