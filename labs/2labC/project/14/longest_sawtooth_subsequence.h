#ifndef INC_9_LONGEST_SAWTOOTH_SUBSEQUENCE_H
#define INC_9_LONGEST_SAWTOOTH_SUBSEQUENCE_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int tvalue;

typedef enum is_comparison_is_strict
{
    comparison_is_strict = 1,
    comparison_is_not_strict = 0,
}is_comparison_is_strict;

int find_the_longest_sawtooth_subsequence(
        tvalue const *sequence,
        size_t sequence_len,
        size_t *subsequence_start_index_storage,
        size_t *subsequence_length_storage,
        int (*comparer)(tvalue const *, tvalue const *),
        int is_comparison_is_strict);

int comparer(tvalue const *, tvalue const *);

#endif //INC_9_LONGEST_SAWTOOTH_SUBSEQUENCE_H
