#include <CowPi.h>
#include "display.h"

void setup() {
    cowpi_setup(0,
                (cowpi_display_module_t) {.display_module = NO_MODULE},
                (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL}
    );
    initialize_display(16);
    draw_logo();
    delay(2000);
    clear_display();
    print_versions();
}

void loop() {
    static char buffer[18];
    if (cowpi_left_switch_is_in_left_position()) {
        cowpi_illuminate_left_led();
        cowpi_deluminate_right_led();
    } else {
        cowpi_illuminate_right_led();
        cowpi_deluminate_left_led();
    }
    if (cowpi_left_button_is_pressed()) {
        for (;;) {}
    }
    count_visits(7);
}