#ifndef INC_9_SUMS_DECOMPOSITION_H
#define INC_9_SUMS_DECOMPOSITION_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int decompose_value(
        int value,
        int start,
        int *current_decomposition,
        size_t current_decomposition_size,
        int allowed_equal_sum_components,
        int ***result_array_of_decompositions,
        size_t *decompositions_count,
        size_t *capacity);

int sums_decomposition(
        int value,
        int ***result_decompositions,
        size_t *result_decompositions_count,
        int allowed_equal_sum_components);

void print_decompositions(
        int **array_of_decompositions,
        size_t count_of_decompositions);

#endif //INC_9_SUMS_DECOMPOSITION_H
