#ifndef INC_9_SUBSTR_REALIZATION_H
#define INC_9_SUBSTR_REALIZATION_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SUBSTR_NOT_FOUND -1

void free_elements_of_array(
        char **results,
        int **positions,
        size_t capacity
        );

int to_find_substring(
        const char* str,
        const char* substr,
        int case_sensitive,
        size_t *str_index);


int substr(
        char *to_find,
        int case_register_sensitive,
        char ***results, int ***positions,
        size_t* results_count, ...);

#endif //INC_9_SUBSTR_REALIZATION_H
