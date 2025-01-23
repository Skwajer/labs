#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

void my_strrev(char* str)
{
    size_t lena = strlen(str);
    int i;
    size_t j;
    char temp;

    for (i = 0, j = lena - 1; i < j; ++i, --j)
    {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
}

int inverse_gorner(
        unsigned long long num,
        unsigned int const base,
        char* result_placement)
{
    int i = 0, digit;

    if (base < 2 || base > 36)
    {
        return 1;
    }

    if (result_placement == NULL)
    {
        return 2;
    }

    do
    {
        digit = num % base;
        result_placement[i++] = (digit < 10)
                                ? digit + '0'
                                : digit - 10 + 'A';
        num /= base;
    } while (num > 0);

    result_placement[i] = 0;

    my_strrev(result_placement);

    return 0;
}

int gorner(
        char const* str_num,
        unsigned int const base,
        unsigned long long* result_placement)
{
    unsigned long long result = 0;

    if (result_placement == NULL)
    {
        return 1;
    }

    if (str_num == NULL || !*str_num)
    {
        return 2;
    }

    if (base < 2 || base > 36)
    {
        return 3;
    }

    while (*str_num)
    {
        if (!((isdigit(*str_num) && *str_num - '0' < base) ||
              (isalpha(*str_num) && toupper(*str_num) - 'A' < base - 10)))
        {
            return 2;
        }

        result = result * base + (isdigit(*str_num)
                                  ? *str_num - '0'
                                  : toupper(*str_num) - 'A' + 10);

        ++str_num;
    }

    *result_placement = result;

    return 0;
}

int to_search_kaprekar_numbers(
        unsigned int const base,
        size_t const count_of_numbers,
        ...)
{
    int status, i, j, k;
    unsigned long long number, square_number, left_part_number, right_part_number;
    char* temp;
    char const* number_str;
    char left_part[BUFSIZ], right_part[BUFSIZ], square_number_str[BUFSIZ];
    size_t square_number_str_size;
    va_list args;

    if (base < 2 || base > 36)
    {
        return 1;
    }

    if (count_of_numbers == 0)
    {
        return 2;
    }

    va_start(args, count_of_numbers);

    for (i = 0; i < count_of_numbers; ++i)
    {
        number_str = va_arg(args, char*);

        status = gorner(number_str, base, &number);

        if (status == 1)
        {
            break;
        }
        else if (status == 2)
        {
            continue;
        }
        else if (status == 3)
        {
            break;
        }

        if (number == 0)
        {
            continue;
        }
        else if (number == 1)
        {
            printf("%s in base %u is a kaprekar number =)\n", number_str, base);

            continue;
        }

        square_number = number * number;

        status = inverse_gorner(square_number, base, square_number_str);

        if (status == 1)
        {
            break;
        }
        else if (status == 2)
        {
            break;
        }

        square_number_str_size = strlen(square_number_str);

        for (k = 1; k < square_number_str_size; ++k)
        {
            temp = square_number_str;

            j = 0;

            while (j < k)
            {
                left_part[j] = *temp;

                ++j;
                ++temp;
            }

            left_part[j] = 0;

            j = 0;

            while (*temp)
            {
                right_part[j] = *temp;

                ++j;
                ++temp;
            }

            right_part[j] = 0;

            status = gorner(left_part, base, &left_part_number);

            if (status == 1)
            {
                break;
            }
            else if (status == 2)
            {
                continue;
            }
            else if (status == 3)
            {
                break;
            }

            status = gorner(right_part, base, &right_part_number);


            if (status == 1)
            {
                break;
            }
            else if (status == 2)
            {
                continue;
            }
            else if (status == 3)
            {
                break;
            }

            if (left_part_number + right_part_number == number)
            {
                printf("%s in base %u is a kaprekar number =)\n", number_str, base);

                break;
            }
        }
    }
    va_end(args);
    return 0;
}
int main()
{
    switch (to_search_kaprekar_numbers(16, 16, "23", "2", "1", "6", "A", "F", "33", "55", "5B", "78", "88", "AB", "CD", "FF", "15F", "334"))
    {
        case 0:
            printf("ALL GOOD!!!!!!!! BRO \n");

            break;

        case 1:
            printf("Invalid base!!!!!\n");

            break;

        case 2:
            printf("HOWWWWWWWW\n");

            break;

        default:
            printf("Undefined behavior 000___ooo\n");

            break;
    }

    return EXIT_SUCCESS;
}