#ifndef INC_1_TASK2_CLASS_DEFINITION_H
#define INC_1_TASK2_CLASS_DEFINITION_H
#include <iostream>
#include <cstring>

class logical_values_array
{
private:
    unsigned int _value;

public:
    logical_values_array(unsigned int init_value = 0);

    unsigned int getter()
    {return _value;}

    unsigned int operator[](size_t bit_number) const;

    unsigned int get_bit(size_t bit_number) const;

    logical_values_array logical_not() const;
    logical_values_array logical_or(logical_values_array const &) const;
    logical_values_array logical_and(logical_values_array const &) const;
    logical_values_array logical_imp(logical_values_array const &) const;
    logical_values_array logical_coimp(logical_values_array const &) const;
    logical_values_array logical_invers(logical_values_array const &) const;
    logical_values_array logical_xor(logical_values_array const &) const;
    logical_values_array logical_equal(logical_values_array const &) const;
    logical_values_array logical_pierce(logical_values_array const &) const;
    logical_values_array logical_sheffer(logical_values_array const &) const;


    static int equals(logical_values_array &, logical_values_array &);

    void dec_to_bin_str(char *) const;
};
#endif //INC_1_TASK2_CLASS_DEFINITION_H
