#include "tokenize_realization.h"

int main()
{
    char input_str[BUFSIZ] = " ngfh\ngfdsgd;f\tgkl dfl; gkdf;lg";
    int accept_empty_lexems = 0, i, err;
    char **lexems;
    size_t lexems_count = 0;

    err = tokenize(input_str, detector, 0, &lexems, &lexems_count);
    if (err)
    {
        return err;
    }

    for (i = 0; i < lexems_count; ++i)
    {
        printf("current token = %s\n", lexems[i]);
        free(lexems[i]);
    }
    printf("%llu", lexems_count);
    free(lexems);

    return OK;
}