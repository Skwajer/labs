#include "sums_decomposition.h"

int decompose_value(
        int value,
        int start,
        int *current_decomposition,
        size_t current_decomposition_size,
        int allowed_equal_sum_components,
        int ***result_array_of_decompositions,
        size_t *decompositions_count,
        size_t *capacity)
{
    int err, i, next_start;
    if (value == 0)
    {
        if (*decompositions_count >= *capacity)
        {
            *capacity *= 2;
            err = my_realloc((void **)(result_array_of_decompositions), (*capacity) * sizeof(int *));
            if (err)
            {
                return err;
            }
        }
        (*result_array_of_decompositions)[*decompositions_count] = (int *)malloc((current_decomposition_size + 1) *
                                                                                  sizeof(int));
        (*result_array_of_decompositions)[*decompositions_count][0] = current_decomposition_size;

        for (i = 0; i < current_decomposition_size; ++i)
        {
            (*result_array_of_decompositions)[*decompositions_count][i + 1] = current_decomposition[i];
        }
        (*decompositions_count)++;

        return OK;
    }

        for (i = start; i <= value; ++i)
        {
            current_decomposition[current_decomposition_size] = i;
            next_start = (allowed_equal_sum_components == 0? i + 1 : i);

            decompose_value(value - i, next_start,
                            current_decomposition,current_decomposition_size + 1,
                            allowed_equal_sum_components,
                            result_array_of_decompositions, decompositions_count,
                            capacity);
        }
    return OK;
}

int sums_decomposition(
        int value,
        int ***result_decompositions,
        size_t *result_decompositions_count,
        int allowed_equal_sum_components)
{
    int *current_decomposition;
    size_t capacity = 16;
    if (result_decompositions == NULL) {return 1;}

    if (result_decompositions_count == NULL) {return 2;}

    if (value < 1) {return 3;}

    *result_decompositions_count = 0;

    *result_decompositions = malloc(capacity * sizeof(int *));
    if (*result_decompositions == NULL)
    {
        return 4;
    }

    current_decomposition = (int *)malloc(value * sizeof(int));
    if (current_decomposition == NULL)
    {
        free(*result_decompositions);
        return 4;
    }

    decompose_value(value, 1, current_decomposition, 0, allowed_equal_sum_components, result_decompositions,
                    result_decompositions_count, &capacity);

    free(current_decomposition);

    return OK;
}

void print_decompositions(
        int **array_of_decompositions,
        size_t count_of_decompositions)
{
    int i, j;
    size_t current_dec_size;
    for (i = 0; i < count_of_decompositions; ++i)
    {
        printf("[");
        current_dec_size = (array_of_decompositions)[i][0];
        for (j = 1; j <= current_dec_size; ++j)
        {
            printf("%d%s", array_of_decompositions[i][j], (j == current_dec_size) ? "" : ", ");
        }
        free(array_of_decompositions[i]);
        printf("]\n");
    }
    free(array_of_decompositions);
}