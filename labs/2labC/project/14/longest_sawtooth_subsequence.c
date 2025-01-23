#include "longest_sawtooth_subsequence.h"

int find_the_longest_sawtooth_subsequence(
        tvalue const *sequence,
        size_t sequence_len,
        size_t *subsequence_start_index_storage,
        size_t *subsequence_length_storage,
        int (*comparer)(tvalue const *, tvalue const *),
        int is_comparison_is_strict)
{
    int i, compare_current_and_left = 0, compare_current_and_right = 0, current_subseq_len = 0,
    is_curr_elem_sawtooth_flag = 0, comparison_result = 0;
    size_t curr_max_subsequence_start_index_storage;

    if (sequence == NULL) {return 1;}

    if (subsequence_start_index_storage == NULL) {return 2;}

    if (subsequence_length_storage == NULL) {return 3;}

    if (comparer == NULL) {return 4;}

    *subsequence_length_storage = 0;
    *subsequence_start_index_storage = -1;

    for (i = 0; i < sequence_len; ++i)
    {
        if (is_curr_elem_sawtooth_flag == 0)
        {
            curr_max_subsequence_start_index_storage = i;
        }
            if (i == 0)
            {
                compare_current_and_right = comparer(sequence + i, sequence + i - 1);
                compare_current_and_left = compare_current_and_right;
            }

            else if(i == sequence_len - 1)
            {
                compare_current_and_left = comparer(sequence + i, sequence + i - 1);
                compare_current_and_right = compare_current_and_left;
            }

            else
            {
                compare_current_and_left = comparer(sequence + i, sequence + i - 1);
                compare_current_and_right = comparer(sequence + i, sequence + i + 1);
            }

            if (is_comparison_is_strict)
            {
                comparison_result = (((compare_current_and_left > 0) && (compare_current_and_right > 0)) ||
                    ((compare_current_and_left < 0) && (compare_current_and_right < 0)));
            }

            else
            {
                comparison_result = (((compare_current_and_left >= 0) && (compare_current_and_right >= 0)) ||
                        ((compare_current_and_left <= 0) && (compare_current_and_right <= 0)));
            }

            if (comparison_result)
            {
                is_curr_elem_sawtooth_flag = 1;
                current_subseq_len += 1;
            }

            else
            {
                is_curr_elem_sawtooth_flag = 0;
                if (*subsequence_length_storage < current_subseq_len)
                {
                    *subsequence_length_storage = current_subseq_len;
                    *subsequence_start_index_storage = curr_max_subsequence_start_index_storage;
                }
                current_subseq_len = 0;
            }
        }
    if (*subsequence_length_storage < current_subseq_len)
    {
        *subsequence_length_storage = current_subseq_len;
        *subsequence_start_index_storage = curr_max_subsequence_start_index_storage;
    }
    return OK;
}

int comparer(tvalue const *value1, tvalue const *value2)
{
    return *value1 - *value2;
}

