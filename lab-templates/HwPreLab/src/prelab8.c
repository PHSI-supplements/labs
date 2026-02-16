/**************************************************************************//**
 *
 * @file prelab8.c
 *
 * @author Christopher A. Bohn
 *
 * @brief  A simple program for a Cow Pi development board that students can
 *      use to establish that they can compile a program.
 *
 ******************************************************************************/

/* Hardware Prelabs (c) 2021-25 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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