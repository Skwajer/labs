#include "task3_class_definition.h"

int main()
{
    complex_number obj1(13, 5);
    complex_number obj2(120, 17);
    complex_number obj3 = obj1 + obj2;
    std::cout << obj1 << " and " << obj2 <<  std::endl;
    std::cout << obj3 <<  std::endl;

    return 0;
}
