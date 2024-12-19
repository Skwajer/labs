#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

typedef enum {
    RESOURCE_FILE,
    RESOURCE_MEMORY,
} ResourceType;

int free_resources(int count, ...);

int main() {
    int* A_ptr = (int*)malloc(2 * sizeof(int));
    if (!A_ptr) {
        perror("Memory allocation error");
        return 1;
    }
    A_ptr[0] = 0;
    A_ptr[1] = 1;

    FILE* f_ptr = fopen("3.txt", "w");
    if (f_ptr == NULL) {
        perror("Error opening file");
        free(A_ptr);
        return 1;
    }

    int err = free_resources(2, RESOURCE_FILE, f_ptr, RESOURCE_MEMORY, A_ptr);
    switch (err) {
        case 1:
            printf("Null pointer encountered for type %d\n");
            return 0;
        case 2:
            printf("Error closing file");
            return 0;
        default:
            printf("all memory is cleared and files are closed");
            return 0;
    }
}

int free_resources(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        ResourceType type = va_arg(args, ResourceType);
        void* ptr = va_arg(args, void*);
        if (ptr == NULL) {
            return 1;

        }
        switch (type) {
            case RESOURCE_FILE:
                if (fclose(ptr) != 0) {
                    return 2;
                }
                break;
            case RESOURCE_MEMORY:
                free(ptr);
                break;
        }
    }
    va_end(args);
    return 0;
}
