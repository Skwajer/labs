#ifndef MAIN_C_TXT_S_F_PRINTF_H
#define MAIN_C_TXT_S_F_PRINTF_H
#include "../../../../libs/errors.h"
#include "../../../../libs/types.h"
#include "../../../../libs/memory.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int printf_calling_function(char  **ANSWER_str,char * restrict _format_, va_list);

int Zeckendorf_number_representation(unsigned int dec_number, unsigned int **ans_array, size_t *count_of_ans_array_elements);


void search_for_fibonacci_number_less_or_equal_to_limit(unsigned int limit, unsigned int *ans);

int over_printf(char const *_format_, ...);

int over_sprintf(char *string, char const *_format_, ...);

int over_fprintf(FILE* file, char const *_format_, ...);

#endif //MAIN_C_TXT_S_F_PRINTF_H
