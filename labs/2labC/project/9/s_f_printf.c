#include "s_f_printf.h"

int Zeckendorf_number_representation(unsigned int dec_number, unsigned int **ans_array, size_t *count_of_ans_array_elements);

int from_int_to_roman_representation(int dec_num, char **ans_str);

int printf_calling_function(char  **ANSWER_str,char  * restrict _format_, va_list vaList_args)
{
    unsigned int *u_z_numbers_array = NULL, uns_num;
    size_t len_format_, capacity = BUFSIZ, count_of_ans_array_elements = 0, size_of_type;
    size_t current_format_index = 0, current_ANSWER_str_index = 0;
    char *temp_ans_str = NULL, *strstr_ans = NULL, *strstr_ans_copy = NULL, *the_input_va_arg_str = NULL;
    int error, i, base, int_num;
    float float_num;
    double double_num;
    unsigned char *u_c_ptr = NULL;



    len_format_ = strlen(_format_);

    temp_ans_str = malloc(capacity * sizeof(char));
    if (temp_ans_str == NULL)
        return MEMORY_ALLOCATION_ERROR;


    while (current_format_index <= len_format_)
    {
        if (capacity - BUFSIZ < current_ANSWER_str_index)
        {
            error = my_realloc((void **) &temp_ans_str, capacity * 2);
            if (error) {
                return error;
            }
            capacity *= 2;
        }
            if (*_format_ == '%')
            {
                switch (*(_format_ + 1))
                {
                    case 'd':
                        error = citoa(va_arg(vaList_args, int), 10, &strstr_ans);
                        if (error)
                        {
                            free(temp_ans_str);
                            temp_ans_str = NULL;
                            return INVALID_PARAMETER;
                        }
                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        free(strstr_ans);
                        strstr_ans = NULL;
                        _format_ += 2;
                        current_format_index += 2;
                        break;

                    case 'u':
                        error = cutoa(va_arg(vaList_args, unsigned int), 10, &strstr_ans);
                        if (error)
                        {
                            free(temp_ans_str);
                            temp_ans_str = NULL;
                            return INVALID_PARAMETER;
                        }
                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        free(strstr_ans);
                        strstr_ans = NULL;
                        _format_ += 2;
                        current_format_index += 2;
                        break;

                    case 'f':
                        error = dec_float_to_str(va_arg(vaList_args, double), &strstr_ans);
                        if (error)
                        {
                            free(temp_ans_str);
                            temp_ans_str = NULL;
                            return INVALID_PARAMETER;
                        }
                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        free(strstr_ans);
                        strstr_ans = NULL;
                        _format_ += 2;
                        current_format_index += 2;
                        break;

                    case 'l':
                        if (*(_format_ + 2) == 'f')
                        {
                            error = dec_float_to_str(va_arg(vaList_args, double), &strstr_ans);
                            if (error)
                            {
                                free(temp_ans_str);
                                temp_ans_str = NULL;
                                return INVALID_PARAMETER;
                            }
                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            free(strstr_ans);
                            strstr_ans = NULL;
                            _format_ += 3;
                            current_format_index += 3;
                        }
                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 'c':
                        temp_ans_str[current_ANSWER_str_index] = va_arg(vaList_args, int);
                        current_ANSWER_str_index += 1;
                        _format_ += 2;
                        current_format_index += 2;
                        break;

                    case 's':
                        strstr_ans = va_arg(vaList_args, char *);
                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        free(strstr_ans);
                        _format_ += 2;
                        current_format_index += 2;
                        strstr_ans = NULL;
                        break;

                    case 'o':
                        error = citoa(va_arg(vaList_args, int), 8, &strstr_ans);
                        if (error)
                        {
                            return error;
                        }
                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        free(strstr_ans);
                        _format_ += 2;
                        current_format_index += 2;
                        strstr_ans = NULL;
                        break;

                    case 'x':
                        error = (citoa(va_arg(vaList_args, int), 8, &strstr_ans));
                        if (error)
                        {
                            return error;
                        }

                        strstr_ans_copy = strstr_ans;
                        while (*strstr_ans_copy)
                        {
                            *strstr_ans_copy = tolower(*strstr_ans_copy);
                            strstr_ans_copy++;
                        }

                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        _format_ += 2;
                        current_format_index += 2;
                        free(strstr_ans);
                        strstr_ans = NULL;
                        strstr_ans_copy = NULL;
                        break;

                    case 'X':
                        error = (citoa(va_arg(vaList_args, int), 8, &strstr_ans));
                        if (error)
                        {
                            return error;
                        }

                        strstr_ans_copy = strstr_ans;
                        while (*strstr_ans_copy)
                        {
                            *strstr_ans_copy = toupper(*strstr_ans_copy);
                            strstr_ans_copy++;
                        }

                        memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                        current_ANSWER_str_index += strlen(strstr_ans);
                        _format_ += 2;
                        current_format_index += 2;
                        free(strstr_ans);
                        strstr_ans = NULL;
                        strstr_ans_copy = NULL;
                        break;

                    case 'R':
                        if (*(_format_ + 2) == 'o')
                        {
                            int_num = va_arg(vaList_args, int);
                            error = from_int_to_roman_representation(int_num, &strstr_ans);
                            if (error)
                            {
                                return error;
                            }
                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            _format_ += 3;
                            current_format_index += 3;
                            free(strstr_ans);
                            strstr_ans = NULL;
                            strstr_ans_copy = NULL;
                        }
                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 'Z':
                        if (*(_format_ + 2) == 'r')
                        {
                            uns_num = va_arg(vaList_args, unsigned int);
                            error = Zeckendorf_number_representation(uns_num, &u_z_numbers_array, &count_of_ans_array_elements);
                            if (error)
                            {
                                free(u_z_numbers_array);
                                return error;
                            }

                            for (i = 0; i < count_of_ans_array_elements; i++)
                            {
                                error = cutoa(u_z_numbers_array[i], 10, &strstr_ans);
                                if (error)
                                {
                                    free(u_z_numbers_array);
                                    u_z_numbers_array = NULL;
                                    return error;
                                }

                                memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                                free(strstr_ans);
                                strstr_ans = NULL;
                                current_ANSWER_str_index += strlen(strstr_ans);
                                temp_ans_str[current_ANSWER_str_index] = ' ';
                                current_ANSWER_str_index += 1;
                            }
                            _format_ += 3;
                            current_format_index += 3;
                            free(u_z_numbers_array);
                            u_z_numbers_array = NULL;
                        }

                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 'C':
                        if (*(_format_ + 2) == 'v')
                        {

                            int_num = va_arg(vaList_args, int);
                            base = va_arg(vaList_args, int);

                            if (base < 2 || base > 36) {base = 10;}
                            citoa(int_num, base, &strstr_ans);

                            i = 0;
                            while (strstr_ans[i])
                            {
                                strstr_ans[i] = tolower(strstr_ans[i]);
                                i++;
                            }
                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            _format_ += 3;
                            current_format_index += 3;
                            free(strstr_ans);
                            strstr_ans = NULL;

                        }

                        else if (*(_format_ + 2) == 'V')
                        {
                            int_num = va_arg(vaList_args, int);
                            base = va_arg(vaList_args, int);

                            if (base < 2 || base > 36) {base = 10;}
                            citoa(int_num, base, &strstr_ans);

                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            _format_ += 3;
                            current_format_index += 3;
                            free(strstr_ans);
                            strstr_ans = NULL;
                        }

                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 't':
                        if (*(_format_ + 2) == 'o')
                        {
                            the_input_va_arg_str = va_arg(vaList_args, char *);
                            base = va_arg(vaList_args, int);
                            if (base < 2 || base > 36) {base = 10;}

                            i = 0;
                            while (the_input_va_arg_str[i])
                            {
                                strstr_ans[i] = tolower(the_input_va_arg_str[i]);
                                i++;
                            }

                            catoi(the_input_va_arg_str, base, &int_num);
                            citoa(int_num, 10, &strstr_ans);

                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            _format_ += 3;
                            current_format_index += 3;
                            free(strstr_ans);
                            strstr_ans = NULL;
                        }

                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 'T':
                        if (*(_format_ + 2) == 'O')
                        {
                            the_input_va_arg_str = va_arg(vaList_args, char *);
                            base = va_arg(vaList_args, int);
                            if (base < 2 || base > 36) {base = 10;}

                            i = 0;
                            while (the_input_va_arg_str[i])
                            {
                                strstr_ans[i] = toupper(the_input_va_arg_str[i]);
                                i++;
                            }

                            catoi(the_input_va_arg_str, base, &int_num);
                            citoa(int_num, 10, &strstr_ans);

                            memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                            current_ANSWER_str_index += strlen(strstr_ans);
                            _format_ += 3;
                            current_format_index += 3;
                            free(strstr_ans);
                            strstr_ans = NULL;
                        }

                        else
                        {
                            temp_ans_str[current_ANSWER_str_index] = '%';
                            _format_++;
                            current_format_index++;
                            current_ANSWER_str_index++;
                        }
                        break;

                    case 'm':
                        switch(*(_format_ + 2))
                        {
                            case 'i':
                                int_num = va_arg(vaList_args, int);

                                u_c_ptr = (unsigned char *)&int_num;

                                size_of_type = sizeof(int);
                                for (i = 0; i < size_of_type; i++)
                                {
                                    error = citoa(*(u_c_ptr)++, 2, &strstr_ans);
                                    if (error)
                                    {
                                        return error;
                                    }
                                    memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                                    current_ANSWER_str_index += strlen(strstr_ans);
                                    free(strstr_ans);
                                    strstr_ans = NULL;
                                    temp_ans_str[current_ANSWER_str_index] = ' ';
                                    current_ANSWER_str_index += 1;
                                }
                                u_c_ptr = NULL;
                                current_format_index += 3;
                                _format_ += 3;
                                break;

                            case 'u':
                                uns_num = va_arg(vaList_args, unsigned int);

                                u_c_ptr = (unsigned char *)&uns_num;

                                size_of_type = sizeof(unsigned int);
                                for (i = 0; i < size_of_type; i++)
                                {
                                    error = citoa(*(u_c_ptr)++, 2, &strstr_ans);
                                    if (error)
                                    {
                                        return error;
                                    }
                                    memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                                    current_ANSWER_str_index += strlen(strstr_ans);
                                    free(strstr_ans);
                                    strstr_ans = NULL;
                                    temp_ans_str[current_ANSWER_str_index] = ' ';
                                    current_ANSWER_str_index += 1;
                                }
                                u_c_ptr = NULL;
                                current_format_index += 3;
                                _format_ += 3;
                                break;

                            case 'f':
                                float_num = va_arg(vaList_args, double);

                                u_c_ptr = (unsigned char *)&float_num;

                                size_of_type = sizeof(float);
                                for (i = 0; i < size_of_type; i++)
                                {
                                    error = citoa(*(u_c_ptr)++, 2, &strstr_ans);
                                    if (error)
                                    {
                                        return error;
                                    }
                                    memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                                    current_ANSWER_str_index += strlen(strstr_ans);
                                    free(strstr_ans);
                                    strstr_ans = NULL;
                                    temp_ans_str[current_ANSWER_str_index] = ' ';
                                    current_ANSWER_str_index += 1;
                                }
                                u_c_ptr = NULL;
                                current_format_index += 3;
                                _format_ += 3;
                                break;

                            case 'd':
                                double_num = va_arg(vaList_args, double);

                                u_c_ptr = (unsigned char *)&double_num;

                                size_of_type = sizeof(double);
                                for (i = 0; i < size_of_type; i++)
                                {
                                    error = citoa(*(u_c_ptr)++, 2, &strstr_ans);
                                    if (error)
                                    {
                                        return error;
                                    }
                                    memcpy(temp_ans_str + current_ANSWER_str_index, strstr_ans, strlen(strstr_ans));
                                    current_ANSWER_str_index += strlen(strstr_ans);
                                    free(strstr_ans);
                                    strstr_ans = NULL;
                                    temp_ans_str[current_ANSWER_str_index] = ' ';
                                    current_ANSWER_str_index += 1;
                                }
                                u_c_ptr = NULL;
                                current_format_index += 3;
                                _format_ += 3;
                                break;

                            default:
                                temp_ans_str[current_ANSWER_str_index] = '%';
                                _format_++;
                                current_format_index++;
                                current_ANSWER_str_index++;
                        }
                        break;

                }
            }

        if (*_format_ != '%') {
            temp_ans_str[current_ANSWER_str_index] = *_format_;
            current_ANSWER_str_index += 1;
            current_format_index += 1;
            _format_++;
        }
    }
    *ANSWER_str = temp_ans_str;
    return OK;
}

int over_printf(char const* _format_, ...)
{
    int err;
    char *s_ans, *s_ans_cpy;
    va_list valist_args;
    va_start(valist_args, _format_);
    err = printf_calling_function(&s_ans, _format_, valist_args);
    if (err)
    {
        return err;
    }

    s_ans_cpy = s_ans;
    while (*s_ans_cpy)
    {
        fputc(*s_ans_cpy++, stdout);
    }

    free(s_ans);
    va_end(valist_args);
    return err;
}

int over_fprintf(FILE *file, char const* _format_, ...)
{
    int err;
    char *s_ans, *s_ans_cpy;
    va_list valist_args;
    va_start(valist_args, _format_);
    err = printf_calling_function(&s_ans, _format_, valist_args);
    if (err) {
        return err;
    }

    s_ans_cpy = s_ans;
    while (*s_ans_cpy) {
        fputc(*s_ans_cpy++, file);
    }

    free(s_ans);
    va_end(valist_args);
    return err;
}

int over_sprintf(char *string, char const *_format_, ...)
{
    int err;
    char *s_ans;
    va_list valist_args;
    va_start(valist_args, _format_);
    err = printf_calling_function(&s_ans, _format_, valist_args);
    if (err)
    {
        return err;
    }

    strcpy(string, s_ans);

    free(s_ans);
    va_end(valist_args);
    return err;
}


int from_int_to_roman_representation(int dec_num, char **ans_str) {
    int i = 0, error;
    char *temp = NULL;
    size_t len = 0;
    size_t roman_digit_len;
    struct {
        int value;
        const char *symbol;
    } roman_numerals[] = {{1000, "M"},
                          {900,  "CM"},
                          {500,  "D"},
                          {400,  "CD"},
                          {100,  "C"},
                          {90,   "XC"},
                          {50,   "L"},
                          {40,   "XL"},
                          {10,   "X"},
                          {9,    "IX"},
                          {5,    "V"},
                          {4,    "IV"},
                          {1,    "I"}};
    while (dec_num > 0)
    {
        while (dec_num >= roman_numerals[i].value)
        {
            roman_digit_len = strlen(roman_numerals[i].symbol);
            error = my_realloc((void **) &temp, len + roman_digit_len * sizeof(char));
            if (error)
            {
                return error;
            }
            memcpy(temp + len, roman_numerals[i].symbol, roman_digit_len);
            len += roman_digit_len;
            dec_num -= roman_numerals[i].value;
        }
        error = my_realloc((void **) &temp, (len + 1) * sizeof(char));

        if (error)
        {
            return error;
        }
        temp[len] = 0;
        i++;

    }
    *ans_str = temp;
    return OK;
}

void search_for_fibonacci_number_less_or_equal_to_limit(unsigned int limit, unsigned int *ans)
{
    unsigned int previous_fib1 = 1, previous_fib2 = 1, current_fib = 0;

    current_fib = previous_fib1 + previous_fib2;

    while (current_fib <= limit)
    {
        previous_fib1 = previous_fib2;
        previous_fib2 = current_fib;
        current_fib = previous_fib1 + previous_fib2;
    }
    *ans = previous_fib2;
}

int Zeckendorf_number_representation(unsigned int dec_number, unsigned int **ans_array, size_t *count_of_ans_array_elements)
{
    if (ans_array == NULL)
    {
        return UNEXPECTED_NULL_PTR;
    }

    int error;
    size_t virtual_size = 0, capacity = 16;
    unsigned int current_number_to_add;

    *ans_array = (unsigned int*)malloc(capacity * sizeof(unsigned int));

    if (*ans_array == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    while (dec_number > 0)
    {
        if (virtual_size >= capacity)
        {
            error = my_realloc((void **)ans_array, 2 * capacity * sizeof(unsigned int));
            if (error)
            {
                free(ans_array);
                return error;
            }
        }

        search_for_fibonacci_number_less_or_equal_to_limit(dec_number, &current_number_to_add);
        (*ans_array)[virtual_size] = current_number_to_add;
        virtual_size += 1;
        dec_number -= current_number_to_add;
    }

    error = my_realloc((void **)ans_array, virtual_size * sizeof(unsigned int));
    if (error)
    {
        free(ans_array);
        return error;
    }

    *count_of_ans_array_elements = virtual_size;

    return OK;
}