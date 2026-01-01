/**************************************************************************//**
 *
 * @file sensor.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to manage the distance sensor.
 *
 ******************************************************************************/

/*
 * ProximityAlarmLab assignment and starter code (c) 2023-25 Christopher A. Bohn
 * ProximityAlarmLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "display.h"
#include "common.h"
#include "interrupt_support.h"
#include "sensor.h"


static char buffer[18] = {0};


/**
* @brief Structure to access analog-digital converter's registers.
*/
typedef struct {
    uint32_t control;       //<! control and status register (20:16 RROBIN, 14:12 AINSEL, 10 ERR_STICKY, 9 ERR, 8 READY, 3 START_MANY, 2 START_ONCE, 1 TS_EN, 0 EN)
    uint32_t result;        //!< 12-bit result of last conversion
    // skip over the remaining registers
} adc_t;

static adc_t volatile *const thermometer = (adc_t *) (0x4004c000);


sensor_states_t volatile sensor_state;
bool volatile object_detected;
unsigned int volatile distance_cm;


static void handle_sensor_timer(void);
static void on_pulse_edge(void);
static uint32_t read_temperature_register(void);
static unsigned int compute_distance(uint32_t microseconds, uint32_t temperature_register_value);
static int compute_temperature(uint32_t temperature_register_value);


static uint32_t volatile pulse_start_time;
static uint32_t volatile pulse_end_time;


void initialize_sensor(void) {
    thermometer->control = (1 << 20) | (4 << 12);       // place ADC channel 4 in the round-robin
    thermometer->control |= 3;                          // temperature sensor enable, ADC enable
    cowpi_set_output_pins(1 << TRIGGER_PIN);            // configures the pin
    cowpi_set_floating_input_pins(1 << ECHO_PIN);       // configures the pin
    set_pin_low(TRIGGER_PIN);
    sensor_state = INITIAL_START;
    object_detected = false;
    /* CONFIGURE THE INTERRUPTS/REGISTER THE ISRs HERE */


}

void manage_sensor(void) {
    static sensor_states_t previous_state = -1;
    if (sensor_state != previous_state) {
        previous_state = sensor_state;
        switch (sensor_state) {
            case INITIAL_START:
                display_string(2, "INITIAL_START");
                break;
            case POWERING_UP:
                display_string(2, "POWERING_UP");
                break;
            case READY:
                display_string(2, "READY");
                break;
            case ACTIVE_LISTENING:
                display_string(2, "ACTIVE_LISTENING");
                break;
            case ACTIVE_DETECTED:
                display_string(2, "ACTIVE_DETECTED");
                break;
            case QUIESCENT:
                display_string(2, "QUIESCENT");
                break;
            default:
                sprintf(buffer, "ERROR line %d\n", __LINE__);
                display_string(6, buffer);
        }
    }

    static input_states_t left_button_state = NOT_PRESSED;
    bool left_button_pressed = cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN);
    switch(left_button_state) {
        case NOT_PRESSED:
            if (left_button_pressed) {
                left_button_state = RESPOND_TO_PRESS;
            }
            break;
        case RESPOND_TO_PRESS:
            initiate_pulse();
            left_button_state = PRESSED;
            break;
        case PRESSED:
            if (!left_button_pressed) {
                left_button_state = RESPOND_TO_RELEASE;
            }
            break;
        case RESPOND_TO_RELEASE:
            left_button_state = NOT_PRESSED;
            break;
        default:
            sprintf(buffer, "ERROR line %d\n", __LINE__);
            display_string(6, buffer);
    }
    process_detection();
    sprintf(buffer, "temperature: %2uC", compute_temperature(read_temperature_register()));
    display_string(1, buffer);
}

void initiate_pulse(void) {
    /* YOUR CODE GOES HERE */


}

static void on_pulse_edge(void) {
    if (sensor_state == INITIAL_START || sensor_state == POWERING_UP) {
        return;     // not necessary, but it doesn't hurt
    }
    /* PULSE-RELATED STATE TRANSITIONS GO HERE */


}

static void handle_sensor_timer(void) {
    switch(sensor_state) {
        case INITIAL_START:
            sensor_state = POWERING_UP;
            break;
        case POWERING_UP:
            sensor_state = READY;
            break;
        /* TIMER-RELATED STATE TRANSITIONS GO HERE */


        default:
            // do nothing
            break;
    }
}

void process_detection(void) {
    /* YOUR CODE GOES HERE */


}

static unsigned int compute_distance(uint32_t microseconds, uint32_t temperature_register_value) {
    // DO NOT CALL `compute_temperature` IN THIS FUNCTION!
    // THE EQUATION IN THE ASSIGNMENT USES THE VALUE IN THE TEMPERATURE REGISTER, NOT THE COMPUTED TEMPERATURE!
    uint64_t microseconds64 = (uint64_t) microseconds;
    uint64_t temperature_register_value64 = (uint64_t) temperature_register_value;
    /* YOUR CODE GOES HERE */


    return 0;
}


static uint32_t read_temperature_register(void) {
    thermometer->control |= (4 << 12);                  // sample ADC channel 4 next
    thermometer->control |= (1 << 2);                   // sample and convert once
    while ((thermometer->control & (1 << 8)) == 0) {}   // busy-wait during sampling/conversion
    return thermometer->result;
}

static int compute_temperature(uint32_t temperature_register_value) {
    // USING THE CALCULATED TEMPERATURE IS NOT PART OF THE ASSIGNMENT!
    double adc_voltage = 3.3 * temperature_register_value / 4096;   // 12 bit ADC
    double celsius = 27 - (adc_voltage - 0.706) / 0.001721;         // equation from RP2040 datasheet section 4.9.5
    return (int) round(celsius);
}
