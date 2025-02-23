 #include <malloc.h>
#include "../errors.h"

int my_realloc(void **ptr, size_t size)
{
    void *for_realloc = NULL;
    int error;

    for_realloc = realloc(*ptr, size);
    if (for_realloc == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    *ptr = for_realloc;
    return OK;
}