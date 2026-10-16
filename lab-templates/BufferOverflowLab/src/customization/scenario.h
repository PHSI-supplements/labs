/**************************************************************************//**
 *
 * @file scenario.h
 *
 * @author Christopher A. Bohn
 *
 * @sa ../target/scenario.h
 *
 * @brief Function names for the checkpoints in the scenario's story.
 *
 * The scenario may change from one semester to the next, and so the names of
 *      the checkpoint functions can be customized.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef CUSTOMIZATION_SCENARIO_H
#define CUSTOMIZATION_SCENARIO_H

#include "../target/scenario.h"

#define STACK_NO_CODE_CHECKPOINT        activate_pa_system
#define STACK_CODE_INT_CHECKPOINT       ring_dinner_bell
#define STACK_CODE_STRING_CHECKPOINT    lock_carnivore_enclosures
#define ROP_INT_CHECKPOINT              lock_herbivore_enclosures
#define ROP_STRING_CHECKPOINT           unlock_zoo_gates
#define HEAP_NO_CODE_CHECKPOINT         todo_do_something
#define HEAP_CODE_INT_CHECKPOINT        todo_unlock_zoo_gates

#endif //CUSTOMIZATION_SCENARIO_H
