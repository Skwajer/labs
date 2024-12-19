#include <stdio.h>
#include <malloc.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
        return -1;

    char *flag = argv[1];
    if (flag[0] == '-' && flag[1] == 'c')
    {
        int seed = atoi(argv[2]);
        char *answer_str;
        concatenate_strings(argc, argv, seed, &answer_str);
        printf("concatenated str = %s", answer_str);
        free(answer_str);
    }
    else {
        char *str = argv[2];

        if (flag[0] == '-' && flag[1] == 'l') {
            printf("%d", len_str(str));
        }

        if (flag[0] == '-' && flag[1] == 'r') {
            char *rev_str;
            reverse_str(&str, &rev_str);
            printf("reversed string = %s", rev_str);
            free(rev_str);
        }

        if (flag[0] == '-' && flag[1] == 'u') {
            odd_to_upper(str);
            printf("new string = %s", str);
        }

        if (flag[0] == '-' && flag[1] == 'n') {
            char *answer_str;
            classify_str(str, &answer_str);
            printf("classify str = %s", answer_str);
            free(answer_str);
        }
        return 0;
    }
}

