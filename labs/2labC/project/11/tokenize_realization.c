#include "tokenize_realization.h"

int detector(int ch)
{
    if (ch == '\n' || ch == '\t' || ch == ' ')
    {
        return SEPARATOR;
    }

    return TOKEN_SYMBOL;
}

int tokenize(
        char* initial,
        int (*detector)(int),
        int accept_empty_lexems,
        char*** lexems,
        size_t *lexems_count)
{
    if (initial == NULL)
    {
        return 1;
    }

    if (detector == NULL)
    {
        return 2;
    }

    if (lexems_count == NULL)
    {
        return 4;
    }


    *lexems_count = 0;

    int err, i = 0;
    size_t capacity = BUFSIZ, token_capacity = BUFSIZ, virtual_token_size = 0;
    char *current_token = NULL;

    *lexems = (char **)malloc(capacity * sizeof(char *));
    if (*lexems == NULL)
    {
        return 5;
    }

    if (*initial == 0 && accept_empty_lexems == 0)
    {
        *lexems_count += 1;
        return 100;
    }

    else if (*initial == 0 && accept_empty_lexems == 1)
    {
        (*lexems)[*lexems_count] = (char*)malloc(1);
        if ((*lexems)[*lexems_count] == NULL)
        {
            return 5;
        }
        ((*lexems)[*lexems_count])[virtual_token_size] = '\0';
        *lexems_count += 1;
    }
    if (accept_empty_lexems == 0)
    {
        while (detector(initial[i]) == SEPARATOR)
        {
            i++;
        }
    }
        while (initial[i])
        {

            if (detector(initial[i]) == SEPARATOR && virtual_token_size == 0 && accept_empty_lexems == 1) //обработка пустой лексемы 0_0
            {
                (*lexems)[*lexems_count] = (char*)malloc(1);
                if ((*lexems)[*lexems_count] == NULL)
                {
                    return 5;
                }
                ((*lexems)[*lexems_count])[virtual_token_size] = '\0';
                *lexems_count += 1;
            }

            else if (detector(initial[i]) == SEPARATOR && virtual_token_size == 0 && accept_empty_lexems == 0)
            {
                i++;
            }

            else if (detector(initial[i]) == SEPARATOR && virtual_token_size != 0)
            {
                ((*lexems)[*lexems_count])[virtual_token_size] = '\0';
                virtual_token_size = 0;
                *lexems_count += 1;
            }

            else if(detector(initial[i]) == TOKEN_SYMBOL && virtual_token_size == 0)
            {
                (*lexems)[*lexems_count] = (char *)malloc(token_capacity * sizeof(char));
                if ((*lexems)[*lexems_count] == NULL)
                {
                    return 5;
                }
                ((*lexems)[*lexems_count])[virtual_token_size++] = initial[i];
            }

            else if (detector(initial[i]) == TOKEN_SYMBOL && virtual_token_size != 0)
            {
                ((*lexems)[*lexems_count])[virtual_token_size++] = initial[i];
            }
            i++;
        }

        if (virtual_token_size != 0)
        {
            ((*lexems)[*lexems_count])[virtual_token_size] = '\0';
            *lexems_count += 1;
        }

    return OK;
}