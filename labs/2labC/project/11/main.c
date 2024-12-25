#include "tokenize_realization.h"

int main()
{
    char input_str[BUFSIZ] = "\ndfgd fgd\rfg\n";
    int accept_empty_lexems = 1, i, err;
    char **lexems;
    size_t lexems_count = 0;

    err = tokenize(input_str, detector, accept_empty_lexems, &lexems, &lexems_count);
    if (err)
    {
        return err;
    }

    for (i = 0; i < lexems_count; ++i)
    {
        printf("current token = %s", lexems[i]);
    }

    return OK;
}