#ifndef INC_2_LAB_C_MY_SCANF_H
#define INC_2_LAB_C_MY_SCANF_H

#include "../../../../libs/errors.h"
#include "../../../../libs/memory.h"
#include "../../../../libs/types.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STDIN_STREAM (1)
#define FILE_STREAM (2)
#define STR_STREAM (3)

#define P_INT (1)
#define P_DOUBLE (2)
#define P_CHAR (3)
#define P_FLOAT (4)
#define P_STRING (5)

int roman_to_int(char const *entrance_roman_str, int *answer);

int scan_from_stream(int stream, void **stream_ptr, char dest[BUFSIZ]);

int scanf_calling_function(int stream, void *stream_ptr, char const *_format_, va_list Valist_args);

int over_scanf(char const *format, ...);
int over_fscanf(char const *format, FILE *stream_ptr, ...);
int over_sscanf(char *format, char *stream_ptr, ...);

#endif //INC_2_LAB_C_MY_SCANF_H