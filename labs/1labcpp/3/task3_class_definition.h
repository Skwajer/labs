#ifndef INC_1_TASK3_CLASS_HEADER_H
#define INC_1_TASK3_CLASS_HEADER_H
#include <iostream>
#include <cstring>
#include <cmath>

class complex_number
{
private:
    double real_part;
    double imaginary_part;

public:
    complex_number(double init_real_part = 0, double init_imaginary_part = 0);
    double complex_mod(){return std::sqrt(real_part * real_part + imaginary_part * imaginary_part);}
    double argument(){return std::atan2(real_part, imaginary_part);}
    complex_number& operator+=(complex_number const &obj2);
    complex_number operator+(complex_number const &obj2);
    complex_number& operator*=(complex_number const &obj2);
    complex_number operator*(complex_number const &obj2);
    complex_number& operator/=(complex_number const &obj2);
    complex_number operator/(complex_number const &obj2);

    friend std::ostream& operator<<(std::ostream& os, complex_number& obj);
    friend std::istream& operator>>(std::istream& is, complex_number& obj);
};

#endif //INC_1_TASK3_CLASS_HEADER_H
