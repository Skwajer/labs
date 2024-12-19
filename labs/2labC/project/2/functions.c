#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MEM_ALLOC_ERROR 2;
#define VALUE_ERROR 1;

int reverse_str(char *str[], char *new_str[])
{
    if (*(*str) == '\0')
        return VALUE_ERROR;

    int len = 0;
    while ((*str)[len] != '\0')
    {
        len++;
    }

    if (!(*new_str = (char *)malloc(len + 1)))
        return MEM_ALLOC_ERROR;

    int i, j = 0;
    for (i = len - 1; i >= 0; i--)
    {
        (*new_str)[j++] = (*str)[i];
    }

    (*new_str)[j] = '\0';

    free(*str);

    return 0;
}

int len_str(char const str[])
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int odd_to_upper(char *str)
{
    if (*str == '\0')
        return VALUE_ERROR;

    int i;
    int len = len_str(str);
    for (i = 0; i < len; i += 2)
    {
        str[i] = toupper(str[i]);
    }
    return 0;
}

int classify_str(char const str[], char *sorted_str[])
{
    if (*str == 0)
        return VALUE_ERROR;

    int count_numbers = 0, count_letters = 0, count_unusual_symbols = 0;
    int i;
    int len = len_str(str);

    for (i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
            count_numbers++;

        else if (isalpha(str[i]))
            count_letters++;

        else
            count_unusual_symbols++;

    }
    if (!(*sorted_str = (char *) malloc(sizeof(char) * (len + 1))))
        return MEM_ALLOC_ERROR;

    int j = 0;
    int digit_index = 0, letter_index = count_numbers, other_index = count_numbers + count_letters;

    while (j < len) {
        if (isdigit(str[j])) {
            (*sorted_str)[digit_index++] = str[j];

        } else if (isalpha(str[j])) {
            (*sorted_str)[letter_index++] = str[j];

        } else {
            (*sorted_str)[other_index++] = str[j];
        }
        j++;
    }

    (*sorted_str)[len] = '\0';

    return 0;
}

int concatenate_strings(int argc, char **argv, int seed, char **concatenated_string) {
    if (argc < 4) {
        return VALUE_ERROR; // Недостаточно аргументов
    }

    if (seed < 0 || seed > INT_MAX) {
        return VALUE_ERROR; // Некорректный seed
    }

    srand(seed); // Инициализация генератора случайных чисел

    // Подсчет количества строк, которые нужно конкатенировать
    int string_count = (argc - 3); //  -3 для отсечения флага, seed и строки

    // Выделение памяти для новой строки
    int total_length = 0;
    for (int i = 3; i < argc; i++) {
        total_length += len_str(argv[i]);
    }
    if (!(*concatenated_string = (char *)malloc(sizeof (char) * (total_length + 1)))) // +1 для null-терминатора
        return MEM_ALLOC_ERROR;

    // Создание массива индексов для случайного порядка конкатенации
    int *indexes = malloc(sizeof(int) * string_count);
    if (indexes == NULL) {
        free(concatenated_string);
        return MEM_ALLOC_ERROR; // Ошибка выделения памяти
    }
    for (int i = 0; i < string_count; i++) {
        indexes[i] = i;
    }

    // Перемешивание индексов для случайного порядка
    for (int i = string_count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indexes[i];
        indexes[i] = indexes[j];
        indexes[j] = temp;
    }

    // Конкатенация строк в случайном порядке
    int current_index = 0;
    for (int i = 0; i < string_count; i++) {
        int string_index = indexes[i]+ 3; // Индекс строки в массиве argv
        int len = len_str(argv[string_index]);
        strncpy(*concatenated_string + current_index, argv[string_index], len);
        current_index += len;
    }

    (*concatenated_string)[current_index] = '\0'; // Добавляем null-терминатор

    free(indexes);
    return 0;
}