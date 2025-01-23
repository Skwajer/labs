#ifndef INC_9_FIND_SADDLE_POINTS_H
#define INC_9_FIND_SADDLE_POINTS_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int tvalue;

int find_saddle_points(
        tvalue const * const *matrix,
        size_t matrix_rows_count,
        size_t matrix_columns_count,
        size_t ***found_saddle_points_storage,
        size_t *found_saddle_points_count_storage,
        int (*comparer)(tvalue const *, tvalue const *),
        int is_comparison_is_strict);

int comparer(tvalue const *, tvalue const *);


#endif //INC_9_FIND_SADDLE_POINTS_H
