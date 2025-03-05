#ifndef INC_1LABCPP_TASK4_CLASS_DEFINITION_H
#define INC_1LABCPP_TASK4_CLASS_DEFINITION_H
#include <iostream>
class matrix
{
private:
    double **matrix_values;
    size_t rows, columns;

public:
    matrix(size_t, size_t);
    matrix& operator+=(matrix& obj2);
    matrix operator+(matrix& obj2);
    matrix& operator-=(matrix& obj2);
    matrix operator-(matrix& obj2);
    matrix& operator*=(matrix& obj2);
    matrix& operator*=(double);
    friend matrix operator*(double number, matrix& obj);
    matrix transposed_matrix();
    double determinant();
    matrix inverse_matrix();
    double* operator[](size_t row) const;
    double& operator()(size_t row, size_t column);
};


#endif //INC_1LABCPP_TASK4_CLASS_DEFINITION_H
