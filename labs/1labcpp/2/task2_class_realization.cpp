#include "task2_class_definition.h"

logical_values_array:: logical_values_array(unsigned int init_value)
{
    _value = init_value;
}


unsigned int logical_values_array::get_bit(size_t bit_number) const
{
    if (bit_number > sizeof(unsigned int))
    {
        throw std:: invalid_argument("bit number isn't correct");
    }
    return (_value >> bit_number) & 1;
}


unsigned int logical_values_array ::operator[](size_t bit_number) const
{
    return get_bit(bit_number);
}


void logical_values_array::dec_to_bin_str(char * buf_str) const
{
    if (buf_str == nullptr)
    {
        throw std::invalid_argument("buf_pointer = nullptr :((((");
    }

    size_t buf_str_size = sizeof(unsigned int) * 8;

    int i;
    for(i = buf_str_size; i >= 0; i--)
    {
        buf_str[buf_str_size - i - 1] = ((_value >> i) & 1) ? '1' : '0';
    }
    buf_str[buf_str_size] = '\0';
}

logical_values_array logical_values_array::logical_not() const
{return (~_value);}

logical_values_array logical_values_array::logical_or(const logical_values_array &obj2) const
{return (_value | obj2._value);}

logical_values_array logical_values_array::logical_and(const logical_values_array &obj2) const
{return (_value & obj2._value);}

logical_values_array logical_values_array::logical_xor(const logical_values_array &obj2) const
{return (_value ^ obj2._value);}

logical_values_array logical_values_array::logical_imp(const logical_values_array &obj2) const
{return (~_value | obj2._value);}

logical_values_array logical_values_array::logical_coimp(const logical_values_array &obj2) const
{return (~_value | ~obj2._value);}

logical_values_array logical_values_array::logical_pierce(const logical_values_array &obj2) const
{return ~(_value & obj2._value);}

logical_values_array logical_values_array::logical_sheffer(const logical_values_array &obj2) const
{return ~(_value | obj2._value);}

int logical_values_array::equals(logical_values_array &var1, logical_values_array &var2)
{
    return var1._value - var2._value;
}