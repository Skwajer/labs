#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int to_find_substring(
        const char* str,
        const char* substr)
{
    int i = 0;

    while (substr[i] && str[i] && str[i] == substr[i])
    {
        ++i;
    }

    return substr[i] == 0;
}

int to_find_substrings_in_files(
        const char* substr,
        int count_of_files,
        ...)
{
    if (*substr == 0)
    {
        return 1;
    }

    if (count_of_files < 1)
    {
        return 2;
    }

    va_list files;
    va_start(files, count_of_files);

    int file_index, str_number, i, buffer_index;
    const char* file_name;
    char buffer[BUFSIZ], ch;

    for (file_index = 0; file_index < count_of_files; ++file_index)
    {
        file_name = va_arg(files, const char*);
        FILE* file = fopen(file_name, "r");

        if (!file)
        {
            printf("%s wasnt found.\n", file_name);

            continue;
        }
        else
        {
            printf("Searching substrings in file %s.\n", file_name);
        }

        str_number = 1;
        buffer_index = 0;

        while ((ch = fgetc(file)) != EOF)
        {
            if (ch == '\n')
            {
                buffer[buffer_index] = 0;

                for (i = 0; buffer[i] != 0; ++i)
                {
                    if (to_find_substring(&buffer[i], substr))
                    {
                        printf("	Substring was found in %d string at %d position.\n", str_number, i + 1);
                    }
                }
                buffer_index = 0;

                ++str_number;
            }
            else
            {
                buffer[buffer_index++] = ch;
            }
        }

        if (buffer_index > 0)
        {
            buffer[buffer_index] = 0;

            for (i = 0; buffer[i] != 0; ++i)
            {
                if (to_find_substring(&buffer[i], substr))
                {
                    printf("	Substring was found in %d string at %d position.\n", str_number, i + 1);
                }
            }
        }

        fclose(file);
    }

    va_end(files);

    return 0;
}

int main()
{
    switch (to_find_substrings_in_files("12", 3, "example1.txt", "example2.txt", "example3.txt"))
    {
        case 0:
            printf("OK\n");

            break;

        case 1:
            printf("Substring is empty\n");

            break;

        case 2:
            printf("it is bad");

            break;

        default:
            printf("Undefined behavior\n");

            break;
    }

    return 0;
}