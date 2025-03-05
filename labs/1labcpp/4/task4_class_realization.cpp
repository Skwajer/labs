#include "task4_class_definition.h"

matrix :: matrix(size_t init_rows, size_t init_columns)
{
    size_t i, j;
    rows = init_rows;
    columns = init_columns;
    matrix_values = new double *[rows];

    for (i = 0; i < rows; ++i)
    {
        matrix_values[i] = new double[columns];
        for(j = 0; j < columns; ++j)
        {
            matrix_values[i][j] = 0;
        }
    }
}

double *matrix::operator[](size_t row) const
{
    if (row < 0 || row > rows)
    {
        throw std::invalid_argument("the value of the argument is invalid");
    }
    return matrix_values[row];
}

double& matrix::operator()(size_t row, size_t column)
{
    if (row < 0 || row > rows || column < 0 || column > columns)
    {
        throw std::invalid_argument("the value of the argument is invalid");
    }
    return matrix_values[row][column];
}