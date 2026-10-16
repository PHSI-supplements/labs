/**************************************************************************//**
 *
 * @file scenario.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Vignettes to advance (or reset) the scenario's story.
 *
 * @copydetails scenario.h
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include "scenario.h"

char const *intros[NUMBER_OF_STAGES] = {
        "The megafauna are loose!\nPaul V. Love says that if they hear the dinner bell, they'll move toward their\nfeeding pens. To make sure they all hear the bell, you first need to activate\nthe PA system.",
        "The PA system is now active.\nConnie D. Shun reminds you that if the megafauna hear the dinner bell over the\nzoo's PA system,they will return to the feeding pens in their enclosures.",
        "Responding to the call of the dinner bell, the animals are all returning to\ntheir enclosures, en route to their feeding pens. The last of the carnivores\nhas entered its enclosure, and so it's time to lock the carnivore enclosures.",
        "Terry Vegian calls from the herbivore wing, \"The mountain deer are\nstarting to get skittish. What's taking so long?\"\nIt's time to lock the herbivore enclosures.",
        "The animals are all safely back in their enclosures.\nThe zoo's gates were closed and locked as a precaution when the animals got\nout, and now you need to unlock them.",
};

char const *outros[NUMBER_OF_STAGES][NUMBER_OF_CORE_EXIT_CODES] = {
        // stage 0
        {
                [SCENARIO_INDEX(SUCCESS)]                       = "The PA system turns on, and you can hear a mild electric hum coming from the loudspeakers.",
                [SCENARIO_INDEX(NO_EXPLOIT)]                    = "A giant sloth is very slowly getting away.",
                [SCENARIO_INDEX(MISALIGNED_STACK_POINTER)]      = "A wooly rhinoceros shakes its head in confusion.",
                [SCENARIO_INDEX(INCORRECT_FUNCTION_ARGUMENT)]   = "A twenty-foot giant beaver slaps its tail and begins evaluating the structural integrity of the visitor center.",
                [SCENARIO_INDEX(CAUGHT_SIGNAL)]                 = "A paleolama steals a hat off of a guest.",
                [SCENARIO_INDEX(INCORRECT_CHECKPOINT)]          = "A goyet dog chases its tail.",
                [SCENARIO_INDEX(BYPASSED_PRIMARY_CHECKS)]       = "A pygmy mammoth trumpets in confusion.",
                [SCENARIO_INDEX(UNSUCCESSFUL_INITIALIZATION)]   = "The megafauna stand around, waiting for something to happen.",
                [SCENARIO_INDEX(UNUSED_EXIT_CODE)]              = "Unused exit code in stage 0.",
        },
        // stage 1
        {
                [SCENARIO_INDEX(SUCCESS)]                       = "The dinner bell rings loudly over the PA system. The megafauna look up from what they were doing and turn back toward their enclosures.",
                [SCENARIO_INDEX(NO_EXPLOIT)]                    = "You tap the microphone. \"Is this thing on?\" The herd of Quentin’s pronghorn continues to graze.",
                [SCENARIO_INDEX(MISALIGNED_STACK_POINTER)]      = "The PA system emits a horrible screech of feedback. Several glyptodonts wince and refuse to move.",
                [SCENARIO_INDEX(INCORRECT_FUNCTION_ARGUMENT)]   = "Instead of the dinner bell, an upbeat kazoo rendition of \"Jingle Bells\" echoes across the zoo.",
                [SCENARIO_INDEX(CAUGHT_SIGNAL)]                 = "There's a loud pop, a puff of smoke, and the PA system goes silent.",
                [SCENARIO_INDEX(INCORRECT_CHECKPOINT)]          = "The bell rings—but only in the gift shop. A confused cashier looks around.",
                [SCENARIO_INDEX(BYPASSED_PRIMARY_CHECKS)]       = "The evacuation siren blares. A herd of Irish elk bolt in terror, their enormous antlers tangling in the shrubbery.",
                [SCENARIO_INDEX(UNSUCCESSFUL_INITIALIZATION)]   = "The speakers hum ominously, but no bell rings. The megafauna stare expectantly.",
                [SCENARIO_INDEX(UNUSED_EXIT_CODE)]              = "Unused exit code in stage 1.",
        },
        // stage 2
        {
                [SCENARIO_INDEX(SUCCESS)]                       = "The locking bolts in the to the carnivore enclosures' gates slide gently into the bolt receivers. Everyone lets out a sign of relief.",
                [SCENARIO_INDEX(NO_EXPLOIT)]                    = "A pair of terror birds stalk across the plaza, eyeing the guests like an unattended buffet.",
                [SCENARIO_INDEX(MISALIGNED_STACK_POINTER)]      = "The gate to the Smilodon enclosure slams shut—then immediately springs back open. The sabertooths look intrigued.",
                [SCENARIO_INDEX(INCORRECT_FUNCTION_ARGUMENT)]   = "You confidently lock enclosure C-4. Unfortunately, C-4 contains three very confused steppe bison.",
                [SCENARIO_INDEX(CAUGHT_SIGNAL)]                 = "There’s a shower of sparks from the control panel. The dire wolves take this as encouragement.",
                [SCENARIO_INDEX(INCORRECT_CHECKPOINT)]          = "The cave lion enclosure locks securely. The cave lions are not inside it.",
                [SCENARIO_INDEX(BYPASSED_PRIMARY_CHECKS)]       = "The locks in the carnivore wing buzz but otherwise do nothing. A short-faced bear lumbers forward with professional curiosity.",
                [SCENARIO_INDEX(UNSUCCESSFUL_INITIALIZATION)]   = "The carnivore control panel remains dark. A Smilodon slowly smiles.",
                [SCENARIO_INDEX(UNUSED_EXIT_CODE)]              = "Unused exit code in stage 2.",
        },
        // stage 3
        {
                [SCENARIO_INDEX(SUCCESS)]                       = "The gates to the herbivore enclosures make a loud clang as the locks snap into place. All animals are now secure.",
                [SCENARIO_INDEX(NO_EXPLOIT)]                    = "The ground sloths resume methodically stripping leaves from a decorative oak.",
                [SCENARIO_INDEX(MISALIGNED_STACK_POINTER)]      = "One gate closes at a jaunty angle and immediately jams. A confused short-faced kangaroo nudges it experimentally.",
                [SCENARIO_INDEX(INCORRECT_FUNCTION_ARGUMENT)]   = "You successfully lock enclosure H-2. Unfortunately, H-2 contains only an empty salt lick.",
                [SCENARIO_INDEX(CAUGHT_SIGNAL)]                 = "The control box pops and emits a curl of smoke. Several glyptodonts blink placidly and continue chewing.",
                [SCENARIO_INDEX(INCORRECT_CHECKPOINT)]          = "With a terrible gurgling sound, the aquatic habitat begins to drain. A very interested blunt-snouted dolphin watches the receding waterline.",
                [SCENARIO_INDEX(BYPASSED_PRIMARY_CHECKS)]       = "The pond drains completely! An Akishima whale considers its new career options on land.",
                [SCENARIO_INDEX(UNSUCCESSFUL_INITIALIZATION)]   = "The herbivore gate controls fail to power on. A stag moose leans gently against the fence, experimentally.",
                [SCENARIO_INDEX(UNUSED_EXIT_CODE)]              = "Unused exit code in stage 3.",
        },
        // stage 4
        {
                [SCENARIO_INDEX(SUCCESS)]                       = "The zoo's gates slide open. Waiting at the entrance, the chaperone for a school field-trip wonders what the excitement was about.",
                [SCENARIO_INDEX(NO_EXPLOIT)]                    = "The front gates remain firmly shut. Outside, a tour bus idles.",
                [SCENARIO_INDEX(MISALIGNED_STACK_POINTER)]      = "The gates open halfway, tilt alarmingly, and grind to a crooked stop",
                [SCENARIO_INDEX(INCORRECT_FUNCTION_ARGUMENT)]   = "You confidently unlock Gate B. Gate B leads directly into the pouch lion habitat.",
                [SCENARIO_INDEX(CAUGHT_SIGNAL)]                 = "There is a sharp metallic snap. One gate swings wildly on a single hinge.",
                [SCENARIO_INDEX(INCORRECT_CHECKPOINT)]          = "The door to the utility vehicle garage swings wide open.",
                [SCENARIO_INDEX(BYPASSED_PRIMARY_CHECKS)]       = "The enclosure gates unlock again. A large-toothed sea otter is the first to notice.",
                [SCENARIO_INDEX(UNSUCCESSFUL_INITIALIZATION)]   = "The gate controls are uncooperative. A few guests check their watches.",
                [SCENARIO_INDEX(UNUSED_EXIT_CODE)]              = "Unused exit code in stage 4.",
        }
};
