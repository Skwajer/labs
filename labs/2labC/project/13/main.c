#include "sums_decomposition.h"

int main()
{
    int** decompositions;
    size_t decompositions_count;
    int allow_repeats = 0;
    int value = 80;
    int status;
    status = sums_decomposition(value, &decompositions, &decompositions_count, allow_repeats);
    if (status)
    {
        return status;
    }
    print_decompositions(decompositions, decompositions_count);
}