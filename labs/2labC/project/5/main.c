#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

double vector_product(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3)
{
    return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
}

int is_convex_polygon(
        int* result_placement,
        int count_of_points,
        ...)
{
    int is_convex = 1, sign = 0, i, current_sign;
    double cross, x1, x2, x3, y1, y2, y3, *x, *y;
    va_list args;

    if (count_of_points < 3)
    {
        return 1;
    }

    if (result_placement == NULL)
    {
        return 2;
    }

    x = (double*)malloc((count_of_points) * sizeof(double));

    if (x == NULL)
    {
        return 3;
    }

    y = (double*)malloc((count_of_points) * sizeof(double));

    if (y == NULL)
    {
        free(x);

        return 3;
    }

    va_start(args, count_of_points);

    for (i = 0; i < count_of_points; ++i)
    {
        x[i] = va_arg(args, double);
        y[i] = va_arg(args, double);
    }

    va_end(args);

    for (i = 0; i < count_of_points; ++i)
    {
        x1 = x[i];
        y1 = y[i];
        x2 = x[(i + 1) % count_of_points];
        y2 = y[(i + 1) % count_of_points];
        x3 = x[(i + 2) % count_of_points];
        y3 = y[(i + 2) % count_of_points];

        cross = vector_product(x1, y1, x2, y2, x3, y3);
        current_sign = (cross > 0) - (cross < 0); // 1 if positive, -1 if negative, 0 if 0

        if (current_sign != 0)
        {
            if (sign == 0)
            {
                sign = current_sign;
            }
            else if (sign != current_sign)
            {
                is_convex = 0;

                break;
            }
        }
    }

    if (is_convex == 1)
    {
        *result_placement = 1;
    }
    else if (is_convex == 0)
    {
        *result_placement = 0;
    }

    free(x);
    free(y);

    return 0;
}

int main()
{
    int result;

    switch (is_convex_polygon(&result, 5, -2.0, -2.0, 0.0, -4.0, 2.0, 0.0, 0.0, 4.0, -1.0, 3.0))  // vipukliy 5ugolnik
        //switch (is_convex_polygon(&result, 4, 0.0, 0.0, 4.0, 0.0, 4.0, 4.0, 0.0, 4.0))                // vipukliy kvadrat
        //switch (is_convex_polygon(&result, 5, 0.0, 0.0, 4.0, 0.0, 2.0, 2.0, 4.0, 4.0, 0.0, 4.0))      // nevipukliy 5ugolnik
    {
        case 0:
            if (result == 0)
            {
                printf("Polygon isn`t convex\n");
            }
            else if (result == 1)
            {
                printf("Polygon is convex\n");
            }

            break;

        case 1:
            printf("Polygon must have at least 3 points\n");

            break;

        case 2:
            printf("Invalid result \n");

            break;

        case 3:
            printf("Memory allocation error\n");

            break;

        default:
            printf("Undefined behavior\n");

            break;
    }

    return EXIT_SUCCESS;
}