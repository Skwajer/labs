#include <ftsiface.h>
#include "my_scanf.h"

int scan_from_stream(int stream, void **stream_ptr, char dest[BUFSIZ]) {
    FILE **file_stream;
    char *str_stream;
    char *p_str_stream;
    char *dest_cpy = dest;
    char c = 65;

    if (stream_ptr == NULL || dest == NULL) {
        return UNEXPECTED_NULL_PTR;
    }

    switch (stream) {
        case STDIN_STREAM: {
            c = fgetc(stdin);
            while ((c == ' ' || c == '\t' || c == '\n') && c != EOF) {
                c = fgetc(stdin);
            }
            while (c != '\0' && c != '\n' && c != ' ' && c != '\t') {
                *dest_cpy++ = c;
                c = fgetc(stdin);
            }
            *dest_cpy = 0;
            break;
        }
        case FILE_STREAM: {
            file_stream = (FILE **)stream_ptr;
            c = fgetc(*file_stream);
            while ((c == ' ' || c == '\t' || c == '\n') && c != EOF) {
                c = fgetc(*file_stream);
            }
            while (c != '\0' && c != '\n' && c != ' ' && c != '\t' &&
                   c != EOF) {
                *dest_cpy++ = c;
                c = fgetc(*file_stream);
            }
            *dest_cpy = 0;
            break;
        }
        case STR_STREAM: {
            p_str_stream = *((char **)stream_ptr);
            c = *p_str_stream;
            p_str_stream++;
            while ((c == ' ' || c == '\t' || c == '\n') && c != '\0') {
                c = *p_str_stream;
                p_str_stream++;
            }
            while (c != '\0' && c != '\n' && c != ' ' && c != '\t') {
                *dest_cpy++ = c;
                c = *p_str_stream;
                p_str_stream++;
            }
            *dest_cpy = 0;
            *stream_ptr = p_str_stream;
            break;
        }
        default:
            return INVALID_PARAMETER;
    }

    return OK;
}

int roman_to_int(char const *entrance_roman_str, int *answer)
{
    if (entrance_roman_str == NULL)
    {
        return UNEXPECTED_NULL_PTR;
    }

    size_t len_roman_str = strlen(entrance_roman_str);
    int i = 0, j, temp_value = 0;
    char letter_1, letter_2;

    struct roman_item {
        int value;
        int len;
        char *letter;
    };

    struct roman_item roman_data[] = {
            {1000, 1, "M"}, {900, 2, "CM"}, {500, 1, "D"}, {400, 2, "CD"},
            {100, 1, "C"},  {90, 2, "XC"},  {50, 1, "L"},  {40, 2, "XL"},
            {10, 1, "X"},   {9, 2, "IX"},   {5, 1, "V"},   {4, 2, "IV"},
            {1, 1, "I"}};

    while (i < len_roman_str)
    {
        letter_1 = entrance_roman_str[i];
        letter_2 = entrance_roman_str[i+1];
        for (j = 0 ;j < 13; j++)
        {
            if (roman_data[j].len == 1 && roman_data[j].letter[0] == letter_1)
            {
                temp_value = roman_data[j].value;
            }

            if (roman_data[j].len == 2 && roman_data[j].letter[0] == letter_1 &&roman_data[j].letter[1] == letter_2)
            {
                temp_value = roman_data[j].value;
            }
        }
        *(answer) += temp_value;
        i++;
    }
    return OK;
}

int scanf_calling_function(int stream, void *stream_ptr, char const *_format_, va_list Valist_args)
{
    if (_format_ == NULL || stream_ptr == NULL)
    {
        return UNEXPECTED_NULL_PTR;
    }
    
    int err, current__format__index = 0, i, base;
    char dest[BUFSIZ];
    void *var_ptr;
    
    if (*_format_ == '%')
    {
        switch (*(_format_ + 1))
        {
            case 'd':
               err = scan_from_stream(stream, &stream_ptr, dest);
               if (err)
               {
                   return err;
               }
               var_ptr = va_arg(Valist_args, int *);
               err = catoi(dest, 10, var_ptr);
               if (err)
               {
                   return err;
               }
               _format_ += 2;
               current__format__index += 2;
               break;

            case 'u':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
                var_ptr = va_arg(Valist_args, unsigned int *);
                err = catoi(dest, 10, var_ptr);
                if (err)
                {
                    return err;
                }
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'f':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
//                var_ptr = va_arg(Valist_args, float *);
//                *var_ptr = atof(dest);
                *va_arg(Valist_args, float *) = atof(dest);
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'l':
                if (*(_format_ + 2) == 'f')
                {
                    err = scan_from_stream(stream, &stream_ptr, dest);
                    if (err)
                    {
                        return err;
                    }
                    *va_arg(Valist_args, double *) = atof(dest);
                    _format_ += 2;
                    current__format__index += 2;
                }
                else
                {
                    return INVALID_FLAG;
                }
                break;

            case 'c':
                switch (stream)
                {
                    case STDIN_STREAM:
                        *va_arg(Valist_args, char *) = fgetc(stdin);
                        break;

                    case FILE_STREAM:
                        *va_arg(Valist_args, char *) = fgetc((FILE *)stream_ptr);
                        break;

                    case STR_STREAM:
                        *va_arg(Valist_args, char *) = *(char *)stream_ptr;
                        stream_ptr = (char *)stream_ptr + 1;
                        break;
                }
                break;

            case 's':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
                strcpy(va_arg(Valist_args, char *), dest);
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'o':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
                var_ptr = va_arg(Valist_args, int *);
                err = catoi(dest, 8, var_ptr);
                if (err)
                {
                    return err;
                }
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'x':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
                var_ptr = va_arg(Valist_args, int *);
                err = catoi(dest, 16, var_ptr);
                if (err)
                {
                    return err;
                }
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'X':
                err = scan_from_stream(stream, &stream_ptr, dest);
                if (err)
                {
                    return err;
                }
                var_ptr = va_arg(Valist_args, int *);
                err = catoi(dest, 16, var_ptr);
                if (err)
                {
                    return err;
                }
                _format_ += 2;
                current__format__index += 2;
                break;

            case 'R':
                if (*(_format_ + 2) == 'o')
                {
                    var_ptr = va_arg(Valist_args, int *);

                    err = scan_from_stream(stream, &stream_ptr, dest);
                    if (err)
                    {
                        return err;
                    }

                    err = roman_to_int(dest, var_ptr);
                    if (err)
                    {
                        return err;
                    }
                    _format_ += 3;
                    current__format__index += 3;
                }

                else
                {
                    INVALID_FLAG;
                }
                break;

            case 'Z':
                if (*(_format_ + 2) == 'r')
                {

                }

                else
                {
                    return INVALID_FLAG;
                }

            case 'C':
                if (*(_format_ + 2) == 'v')
                {
                    var_ptr = va_arg(Valist_args, int *);
                    base = va_arg(Valist_args, int);

                    if (base < 2 || base > 36) {base = 10;}

                    err = scan_from_stream(stream, &stream_ptr, dest);
                    if (err)
                    {
                        return err;
                    }

                    err = catoi(dest, base, var_ptr);
                    if (err)
                    {
                        return err;
                    }
                    _format_ += 3;
                    current__format__index += 3;
                }

                else if (*(_format_ + 2) == 'V')
                {
                    var_ptr = va_arg(Valist_args, int *);
                    base = va_arg(Valist_args, int);

                    if (base < 2 || base > 36) {base = 10;}

                    err = scan_from_stream(stream, &stream_ptr, dest);
                    if (err)
                    {
                        return err;
                    }

                    i = 0;
                    while (dest[i])
                    {
                        dest[i] = toupper(dest[i]);
                        ++i;
                    }

                    err = catoi(dest, base, var_ptr);
                    if (err)
                    {
                        return err;
                    }
                    _format_ += 3;
                    current__format__index += 3;
                }

                else
                {
                    return INVALID_FLAG;
                }
                break;
        }
    }
    
    
    
    return OK;
}