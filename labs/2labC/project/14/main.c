#include "longest_sawtooth_subsequence.h"

int main()
{
    tvalue sequence[5] = {10, 10, 2, 5, 1};

    size_t sawtooth_subseq_start_index, sawtooth_subseq_length;
    int err;

    err = find_the_longest_sawtooth_subsequence(sequence, 5, &sawtooth_subseq_start_index, &sawtooth_subseq_length,
                                          comparer, comparison_is_strict);
    if (err)
    {
        return err;
    }
    printf("subseq length = %llu subseq start index = %llu", sawtooth_subseq_length, sawtooth_subseq_start_index);
    return OK;
}