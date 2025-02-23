#include "../errors.h"
#include "../memory.h"
#include <malloc.h>
#include <math.h>
#include <ctype.h>

int cutoa(unsigned int num, int base, char **ans)
{
    int len, digit;
    if (base < 2 || base > 36)
        return INVALID_PARAMETER;

    if (num == 0)
    {
        *ans = (char *)malloc(2 * sizeof(char));
        if (*ans == NULL)
        {
            return MEMORY_ALLOCATION_ERROR;
        }
        (*ans)[0] = '0';
        (*ans)[1] = '\0';
        return OK;
    }

    len = floor(log(num) / log(base)) + 1;

    *ans = (char *)malloc((len + 1) * sizeof(char));
    if (*ans == NULL)
        return MEMORY_ALLOCATION_ERROR;

    char *temp_ptr = *ans;
    temp_ptr = temp_ptr + len;
    *temp_ptr = '\0';
    temp_ptr--;
    while(num)
    {
        digit = num % base;
        num /= base;
        if (digit > 9) {
            *temp_ptr = toupper(digit) + 'A' - 10;
        } else {
            *temp_ptr = digit + '0';
        }
        temp_ptr--;
    }
    return OK;
}

int citoa(int num, int base, char **ans)
{
    int is_negative = 0, len, digit;
    if (base < 2 || base > 36)
        return INVALID_PARAMETER;

    if (num == 0)
    {
        *ans = (char *)malloc(2 * sizeof(char));
        if (*ans == NULL)
        {
            return MEMORY_ALLOCATION_ERROR;
        }
        (*ans)[0] = '0';
        (*ans)[1] = '\0';
        return OK;
    }

    if (num < 0)
    {
        num = abs(num);
        is_negative = 1;
    }


    len = floor(log(num) / log(base)) + 1 + is_negative;

    *ans = (char *)malloc((len + 1) * sizeof(char));
    if (*ans == NULL)
        return MEMORY_ALLOCATION_ERROR;

    char *temp_ptr = *ans;
    if (is_negative)
    {
        *temp_ptr = '-';
    }
    temp_ptr = temp_ptr + len;
    *temp_ptr = '\0';
    temp_ptr--;
    while(num)
    {
        digit = num % base;
        num /= base;
        if (digit > 9) {
            *temp_ptr = toupper(digit) + 'A' - 10;
        } else {
            *temp_ptr = digit + '0';
        }
        temp_ptr--;
    }
    return OK;
}

int catoi(char const *str, int base, int *ans) {
    int num = 0;
    int digit = 0;
    int minus = 0;

    if (str == NULL || ans == NULL)
    {
        return UNEXPECTED_NULL_PTR;
    }

    if (*ans == '\0')
    {
        return INVALID_PARAMETER;
    }

    if (*str == '-')
    {
        minus = 1;
        str++;
    }

    while (*str)
    {
        if (isalpha(*str))
        {
            digit = tolower(*str) - 'a' + 10;
        }

        else if (isdigit(*str))
        {
            digit = *str - '0';
        }
        num = num * base + digit;
        str++;
    }

    *ans = minus ? -num : num;

    return OK;
}

int dec_float_to_str(float num, char **ans) {
    char *str_num = NULL;
    int integer_part, err, len, i, int_end;
    float float_part;

    if (ans == NULL) {
        return UNEXPECTED_NULL_PTR;
    }
    integer_part = (int)num;
    float_part = num - integer_part;

    err = citoa(integer_part, 10, &str_num);
    if (err) {
        return err;
    }
    int_end = (log(integer_part) / log(10)) + 1;
    len = int_end + 1 + 6;  // 1 for '.', 6 for frac. part
    err = my_realloc((void **)&str_num, len + 1);
    if (err) {
        return err;
    }
    str_num[len] = 0;
    str_num[int_end] = '.';

    for (i = int_end + 1; i < len; ++i) {
        float_part *= 10;
        str_num[i] = ((int)float_part) + '0';
        float_part = float_part - (int)float_part;
    }
    *ans = str_num;

    return OK;
}

