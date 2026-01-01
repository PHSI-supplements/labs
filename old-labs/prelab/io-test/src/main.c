#include <CowPi.h>
#include "display.h"

void setup() {
    record_build_timestamp(__FILE__, __DATE__, __TIME__);
    cowpi_setup(0,
                (cowpi_display_module_t) {.display_module = NO_MODULE},
                (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL}
    );
    initialize_display(21);
//    initialize_display(16);
    draw_logo();
    delay(2000);
    clear_display();
    print_versions();
    print_build_timestamps(true);
}

void loop() {
    static char buffer[17];
    static bool left_button_was_pressed = false;
    static bool right_button_was_pressed = false;
    static bool left_switch_was_in_left_position = false;
    static bool right_switch_was_in_left_position = false;
    static uint16_t previous_keys = 0xFFFF;   // this is improbable and will trigger the initial status "update"
    static char keys[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '#', '*'};
    bool left_button_is_pressed = cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN);
    bool right_button_is_pressed = cowpi_debounce_byte(cowpi_right_button_is_pressed(), RIGHT_BUTTON_DOWN);
    bool left_switch_is_in_left_position = cowpi_debounce_byte(cowpi_left_switch_is_in_left_position(),
                                                               LEFT_SWITCH_LEFT);
    bool right_switch_is_in_left_position = cowpi_debounce_byte(cowpi_right_switch_is_in_left_position(),
                                                                RIGHT_SWITCH_LEFT);
    uint16_t current_keys = cowpi_debounce_short(cowpi_get_keypresses(), KEYPAD);
    bool update_is_needed = ((left_button_is_pressed != left_button_was_pressed)
                             || (right_button_is_pressed != right_button_was_pressed)
                             || (left_switch_is_in_left_position != left_switch_was_in_left_position)
                             || (right_switch_is_in_left_position != right_switch_was_in_left_position)
                             || (current_keys != previous_keys));
    if (update_is_needed) {
        left_button_was_pressed = left_button_is_pressed;
        right_button_was_pressed = right_button_is_pressed;
        left_switch_was_in_left_position = left_switch_is_in_left_position;
        right_switch_was_in_left_position = right_switch_is_in_left_position;
        previous_keys = current_keys;
        bool illuminate_left_led = left_button_is_pressed && !left_switch_is_in_left_position;
        bool illuminate_right_led = right_button_is_pressed && !right_switch_is_in_left_position;
        for (uint16_t i = 0; i < 0x10; i++) {
            sprintf(buffer + i, "%c", (current_keys & (1 << i)) ? keys[i] : '-');
        }
        display_string(4, buffer);
        sprintf(buffer, "Switches: %c %c",
               left_switch_is_in_left_position ? 'L' : 'R',
               right_switch_is_in_left_position ? 'L' : 'R');
        display_string(5, buffer);
        sprintf(buffer, "Buttons: %2s %2s",
               left_button_is_pressed ? "DN" : "UP",
               right_button_is_pressed ? "DN" : "UP");
        display_string(6, buffer);
        refresh_display();
        if (illuminate_left_led) {
            cowpi_illuminate_left_led();
        } else {
            cowpi_deluminate_left_led();
        }
        if (illuminate_right_led) {
            cowpi_illuminate_right_led();
        } else {
            cowpi_deluminate_right_led();
        }
    }
    count_visits(7);
}