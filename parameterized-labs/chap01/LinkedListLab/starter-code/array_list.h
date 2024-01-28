/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file array_list.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Structure definitions for array-backed list handle.
 *
 ******************************************************************************/

/*
 * LinkedListLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

struct list_definition {
    word_entry_t **array;
    size_t length;
    size_t allocation;
    size_t index;
};

#endif //ARRAY_LIST_H
