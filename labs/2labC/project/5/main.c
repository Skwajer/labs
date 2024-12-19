#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

int convexity(int n, ...);

typedef struct Point
{
    double x;
    double y;
}Point;



int main()
{


    return 0;
}

int convexity(int n, ...)
{
    if (n < 3)
        return 10;

    va_list node;
    va_start(node, n);
    Point *Points;
    if ((Points = (Point *)malloc(n * sizeof(Point))) == NULL)
    {
        return 1;
    }

    int i;

    for (i = 0; i < n; i++)
    {
        Points[i] = va_arg(node, Point);

    }

}