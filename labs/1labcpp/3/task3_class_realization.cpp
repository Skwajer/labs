#include "task3_class_definition.h"

complex_number::complex_number(double init_real_part, double init_imaginary_part)
{
    real_part = init_real_part;
    imaginary_part = init_imaginary_part;
}

complex_number& complex_number::operator+=(complex_number const &obj2)
{
    real_part += obj2.real_part;
    imaginary_part += obj2.imaginary_part;
    return *this;
}

complex_number complex_number::operator+(complex_number const &obj2)
{
    complex_number temp(real_part, imaginary_part);
    return temp += obj2;
}

complex_number& complex_number::operator*=(const complex_number &obj2)
{
    real_part *= obj2.real_part;
    imaginary_part *= obj2.imaginary_part;
    return *this;
}

complex_number complex_number::operator*(const complex_number &obj2)
{
    complex_number temp(real_part, imaginary_part);
    return temp *= obj2;
}

complex_number& complex_number::operator/=(const complex_number &obj2)
{
    double denominator = obj2.real_part * obj2.real_part + obj2.imaginary_part *obj2.imaginary_part;
    double new_real_part =  (real_part * obj2.real_part + imaginary_part * obj2.imaginary_part) / denominator;
    double new_imaginary_part = (imaginary_part * obj2.real_part - real_part * obj2.imaginary_part) / denominator;
    real_part = new_real_part;
    imaginary_part = new_imaginary_part;
    return *this;
}

complex_number complex_number::operator/(const complex_number &obj2)
{
    complex_number temp(real_part, imaginary_part);
    return temp /= obj2;
}

std::ostream& operator<<(std::ostream& os, complex_number& obj)
{
    os << obj.real_part << " + " << obj.imaginary_part << 'i';
    return os;
}

std::istream& operator>>(std::istream& is, complex_number& obj)
{
    is >> obj.real_part >> obj.imaginary_part;
    return is;
}