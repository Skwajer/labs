#include "substr_realization.h"

int main() {
    char **results;
    int **positions;
    size_t results_count = 0;
    int case_sensitive = 1;
    int i, j;
    char *to_find = "aSd";
    substr(to_find, case_sensitive, &results, &positions, &results_count, "dfgaSdfghj", "aSd", "jhkgasdkasd", NULL);
    for (i = 0; i < results_count; ++i)
    {
        printf("%s", results[i]);
        free(results[i]);
        printf("[%d] ", *(positions[i]));
        free()
    }
}