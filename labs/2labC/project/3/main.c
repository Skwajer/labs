#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define INVALID_FLAG -1

int clear_or_close(int flag, ...) {
    int c;
    void *arg;
    va_list valist;
    c = flag;
    va_start(valist, flag);
    while (1) {
        arg = va_arg(valist, void *);
        if (arg == NULL) {
            return 0;
        }
        if (c == 'f') {
            printf("freeing memory at %p\n", arg);
            free(arg);
        } else if (c == 'c') {
            printf("closing file var at %p\n", arg);
            fclose((FILE *)arg);
        } else {
            printf("\nits not very good\n");
            return INVALID_FLAG;
        }

        c = va_arg(valist, int);
    }
    va_end(valist);
    return 0;
}

int main()
{
    int err;
    char *str = (char *)malloc(23 * sizeof(char));
    int *arr = (int *)malloc(12 * sizeof(int));
    FILE *fptr = fopen("1.txt", "w");

    printf("resources for free: %p %p %p\n\n", str, fptr, arr);

    err = clear_or_close('f', str, 'c', fptr, 'f', arr, 'w', str, 'f', NULL);

    if (err != 0) {
        printf("vse slomalos`\n");
        return err;
    }
    return 0;
}
