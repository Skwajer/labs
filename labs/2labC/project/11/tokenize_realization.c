#include "tokenize_realization.h"

int detector(int ch)
{
    if (ch == '\n' || ch == '\t')
    {
        return SEPARATOR;
    }
    if (ch  == ' ')
    {
        return SPACE_SYMBOL;
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

    *lexems_count = 0;

    int err, i = 0;
    size_t capacity = BUFSIZ, token_capacity = BUFSIZ, virtual_size = 0, virtual_token_size = 0;
    char *current_token = NULL;

    *lexems = (char **)malloc(capacity * sizeof(char *));
    if (*lexems == NULL)
    {
        return 5;
    }

    current_token = **lexems;

    if (detector(initial[i]) == SEPARATOR)
    {
        i++;
    }

    else if (detector(initial[i]) == SPACE_SYMBOL && accept_empty_lexems && detector(initial[i + 1]) == SEPARATOR)
    {
        current_token = (char *)malloc(2 * sizeof(char));
        if (current_token == NULL)
        {
            return 5;
        }
        current_token[0] = ' ';
        current_token[1] = '\0';
        virtual_size++;
    }

    else if (detector(initial[i]) == SPACE_SYMBOL && accept_empty_lexems && initial[i + 1] == '\0')
    {
        current_token = (char *)malloc(2 * sizeof(char));
        if (current_token == NULL)
        {
            return 5;
        }
        current_token[0] = ' ';
        current_token[1] = '\0';
        err = my_realloc((void **)*lexems, sizeof(char *));
        if (err)
        {
            return 5;
        }
    }

    else if (detector(initial[i]) == SPACE_SYMBOL && !accept_empty_lexems)
    {
        i++;
    }


    while (initial[i])
    {
        if (!accept_empty_lexems)
        {
            if ((detector(initial[i]) == SEPARATOR || detector(initial[i]) == SPACE_SYMBOL) &&
                (detector(initial[i]) == SEPARATOR || detector(initial[i]) == SPACE_SYMBOL))
            {
                i++;
            }

            else if (detector(initial[i]) == TOKEN_SYMBOL && detector(initial[i - 1]) == TOKEN_SYMBOL)
            {
                current_token[virtual_token_size++] = initial[i++];
            }

            else if (detector(initial[i]) == TOKEN_SYMBOL &&
                    (detector(initial[i]) == SEPARATOR || detector(initial[i]) == SPACE_SYMBOL))
            {
                current_token = (*lexems)[virtual_size];
                virtual_size++;
                current_token = (char *)malloc(token_capacity * sizeof(char));
                if (current_token == NULL)
                {
                    free(*lexems);
                    return 5;
                }
                current_token[virtual_token_size++] = initial[i++];
            }

            else if ((detector(initial[i]) == SEPARATOR || detector(initial[i]) == SPACE_SYMBOL) &&
                    detector(initial[i - 1]) == TOKEN_SYMBOL)
            {
                current_token[virtual_token_size] = '\0';
                virtual_token_size = 0;
                (*lexems_count)++;
                virtual_size++;
                i++;
            }

        }

        else
        {
            if (detector(initial[i]) == SEPARATOR &&
                detector(initial[i]) == SEPARATOR)
            {
                i++;
            }

            else if ((detector(initial[i]) == TOKEN_SYMBOL || detector(initial[i]) == SPACE_SYMBOL) &&
                    (detector(initial[i]) == TOKEN_SYMBOL || detector(initial[i]) == SPACE_SYMBOL))
            {
                current_token[virtual_token_size++] = initial[i++];
            }

            else if ((detector(initial[i]) == TOKEN_SYMBOL || detector(initial[i]) == SPACE_SYMBOL) &&
                     detector(initial[i]) == SEPARATOR)
            {
                current_token = (*lexems)[virtual_size];
                virtual_size++;
                current_token = (char *)malloc(token_capacity * sizeof(char));
                if (current_token == NULL)
                {
                    free(*lexems);
                    return 5;
                }
                current_token[virtual_token_size++] = initial[i++];
            }

            else if (detector(initial[i]) == SEPARATOR &&
                    (detector(initial[i]) == TOKEN_SYMBOL || detector(initial[i]) == SPACE_SYMBOL))
            {
                current_token[virtual_token_size] = '\0';
                virtual_token_size = 0;
                (*lexems_count)++;
                virtual_size++;
                i++;
            }
        }
    }
    return OK;
}