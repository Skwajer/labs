#include "my_scanf.h"
int main()
{
    char *str = "CI";
    int ans = 0;

    roman_to_int(str, &ans);
    printf("%d", ans);

    return OK;
}