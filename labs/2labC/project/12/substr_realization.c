#include "substr_realization.h"

void free_elements_of_array(
        char **results,
        int **positions,
        size_t capacity)
{
    int i;
    for (i = 0; i < capacity; ++i)
    {
        free(results[i]);
        free(positions[i]);
    }
}

int to_find_substring(const char* str, const char* substr, int case_sensitive, size_t* index) {
    if (str == NULL || substr == NULL || index == NULL) {
        return SUBSTR_NOT_FOUND;
    }

    int str_index;
    int str_len = strlen(str);
    int substr_len = strlen(substr);

    if (substr_len == 0) {
        *index = 0;
        return OK;
    }
    if (str_len < substr_len) {
        return SUBSTR_NOT_FOUND;
    }


    for (str_index = 0; str_index <= str_len - substr_len; str_index++)
    {
        if (case_sensitive)
        {
            if (strncmp(str + str_index, substr, substr_len) == 0)
            {
                *index = str_index;
                return OK;
            }
        }
        else
        {
            int i = 0;
            while (i < substr_len && (str + str_index)[i] != '\0' &&
                   toupper(substr[i]) == toupper((str + str_index)[i]))
            {
                ++i;
            }
            if (i == substr_len) {
                *index = str_index;
                return OK;
            }
        }
    }

    return SUBSTR_NOT_FOUND;
}

int substr(
        char *to_find,
        int case_register_sensitive,
        char ***results,
        int ***positions,
        size_t* results_count, ...)
{
    if (to_find == NULL)
    {
        return 1;
    }

    if (results == NULL)
    {
        return 2;
    }

    if (positions == NULL)
    {
        return 3;
    }

    if (results_count == NULL)
    {
        return 4;
    }

    *results_count = 0;
    char *current_str;
    size_t capacity = 16, results_element_capacity = BUFSIZ, index;
    int err;

    *results = (char**)malloc(capacity * sizeof(char *));
    if (*results == NULL)
    {
        return 5;
    }

    *positions = (int **)malloc(capacity * sizeof(int *));
    if (*positions == NULL)
    {
        return 5;

    }
    va_list vaList_strings;
    va_start(vaList_strings, results_count);
    current_str = va_arg(vaList_strings, char *);

    while (current_str != NULL)
    {
        if (to_find_substring(current_str, to_find, case_register_sensitive, &index) == OK)
        {
            (*results)[*results_count] = (char *)malloc(results_element_capacity * sizeof(char));
            if ((*results)[*results_count] == NULL)
            {
                free(*positions);
                free(*results);
                va_end(vaList_strings);
                return 5;
            }
            (*results)[*results_count] = current_str;

            (*positions)[*results_count] = (int *)malloc(sizeof(int));
            if ((*positions)[*results_count] == NULL)
            {
                free(*positions);
                free(*results);
                va_end(vaList_strings);
                return 5;
            }
            *((*positions)[*results_count]) = index;
            *results_count += 1;
            index = 0;

            if (capacity <= *results_count)
            {
                capacity *= 2;
                err = my_realloc((void**)positions, capacity * sizeof(int *));
                if (err)
                {
                    return 5;
                }
                err = my_realloc((void**)results, capacity * sizeof(char *));
                if (err)
                {
                    return 5;
                }
            }
        }
    current_str = va_arg(vaList_strings, char *);
    }

    if (*results_count == 0)
    {
        free_elements_of_array(*results, *positions, capacity);
        free(*results);
        free(*positions);
    }

    va_end(vaList_strings);
    return OK;
}