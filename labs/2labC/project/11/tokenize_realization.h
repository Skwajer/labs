#ifndef INC_9_TOKENIZE_REALIZATION_H
#define INC_9_TOKENIZE_REALIZATION_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SEPARATOR 0
#define TOKEN_SYMBOL 10

int tokenize(
             char* initial,
             int (*detector)(int),
             int accept_empty_lexems,
             char*** lexems,
             size_t *lexems_count);

int detector(int CH);

#endif //INC_9_TOKENIZE_REALIZATION_H
