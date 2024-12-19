#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#define VALUE_ERROR 1
#define CLEAR_OR_CLOSE_COMPLETE 0

int clear_or_close(void *resource, int action, ...)
{
    va_list node;
    va_start(node, action);
    while (resource != NULL)
    {
        if ((action > 1) || (action < 0))
        {
            return VALUE_ERROR;
        }

        else if (action == 0)
        {
            free(resource);
        }

        else
        {
            fclose((FILE*)resource);
        }
        resource = va_arg(node, void*);
        action = va_arg(node, int);
    }
    return CLEAR_OR_CLOSE_COMPLETE;
}