#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int to_calculate_value_of_polynomial(
        double *result_placement,
        double x,
        int degree,
        ...)
{
    if (result_placement == NULL)
    {
        return 1;
    }

    if (degree < 0)
    {
        return 2;
    }

    va_list args;
    va_start(args, degree);

    double result = 0.0, coefficient;
    int i;

    for (i = 0; i <= degree; ++i)
    {
        coefficient = va_arg(args, double);
        result = result * x + coefficient;
    }

    va_end(args);

    *result_placement = result;

    return 0;
}

int main()
{
    double result;

    switch (to_calculate_value_of_polynomial(&result, 2.0, 3, 5.0, 2.0, -1.5, 2.5))
    {
        case 0:
            printf("%f\n", result); // minimalistic printf

            break;

        case 1:
            printf("Invalid result placement!\n");

            break;

        case 2:
            printf("Unbelievable.\n");

            break;

        default:
            printf("Undefined behavior! 000___ooo\n");

            break;
    }

    return EXIT_SUCCESS;
}