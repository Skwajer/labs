#include "../include/big_int_API.h"

void bigint::dispose()
{
    delete[] _other_digits;
    _other_digits = nullptr;
}

void bigint::copy_from(
        bigint const &other)
{
    _oldest_digit = other._oldest_digit;
    _other_digits = nullptr;

    if (other._other_digits != nullptr)
    {
        _other_digits = new int[*other._other_digits];
        memcpy(_other_digits, other._other_digits, *other._other_digits * sizeof(int));
    }
}

void bigint::move_from(
        bigint &&other)
{
    _oldest_digit = other._oldest_digit;
    other._oldest_digit = 0;

    _other_digits = other._other_digits;
    other._other_digits = nullptr;
}

bigint::~bigint() noexcept
{
dispose();
}

bigint::bigint(
        bigint const &other):
        _other_digits(nullptr)
{
    copy_from(other);
}

bigint::bigint(
        bigint &&other) noexcept:
_other_digits(nullptr)
        {
                move_from(std::move(other));
        }

bigint &bigint::operator=(
        bigint const &other)
{
    if (this != &other)
    {
        dispose();
        copy_from(other);
    }

    return *this;
}

bigint &bigint::operator=(
        bigint &&other) noexcept
{
if (this != &other)
{
dispose();
move_from(std::move(other));
}

return *this;
}

bigint &bigint::init_with(
        int const *digits_array,
        size_t digits_count)
{
    if (digits_array == nullptr)
    {
        throw std::invalid_argument("Pointer to digits array can't be EQ to nullptr");
    }

    if (digits_count == 0)
    {
        throw std::invalid_argument("Digits count can't be EQ to 0");
    }

    dispose();

    if (digits_count == 1)
    {
        _oldest_digit = *digits_array;

        return *this;
    }

    while (digits_count != 1 && ((digits_array[digits_count - 1] == 0 && digits_array[digits_count - 2] >= 0) || (digits_array[digits_count - 1] == -1 && digits_array[digits_count - 2] < 0)))
    {
        --digits_count;
    }

    *(_other_digits = new int[digits_count]) = static_cast<int>(digits_count);
    memcpy(_other_digits + 1, digits_array, (digits_count - 1) * sizeof(int));
    _oldest_digit = digits_array[digits_count - 1];

    return *this;
}

bigint::bigint(
        int const *digits,
        size_t digits_count):
        _other_digits(nullptr)
{
    init_with(digits, digits_count);
}

bigint::bigint(
        char const *string_representation,
        size_t base):
        _other_digits(nullptr)
{
    // TODO: this requires implemented operator+= and operator*=
}

int bigint::get_sign() const noexcept
{
if (_oldest_digit == 0 && _other_digits == nullptr)
{
return 0;
}

// return _oldest_digit > 0
return (_oldest_digit >> ((sizeof(int) << 3) - 1)) == 0
? 1
: -1;
}

size_t bigint::get_digits_count() const noexcept
{
return _other_digits == nullptr
? 1
: *_other_digits;
}

unsigned int bigint::operator[](
        size_t index) const noexcept
{
auto const digits_count = get_digits_count();

if (index >= digits_count)
{
return 0;
}

return *reinterpret_cast<unsigned int const *>(index == digits_count - 1
? &_oldest_digit
: _other_digits + 1 + index);
}

int &bigint::operator[](
        size_t index)
{
    auto const digits_count = get_digits_count();

    if (index >= digits_count)
    {
        throw std::out_of_range("out of range of digits array");
    }

    return index == digits_count - 1
           ? _oldest_digit
           : *(_other_digits + 1 + index);
}

bigint& bigint::invert() &
{
    for (int i = 0; i < get_digits_count(); ++i)
    {
        (*this)[i] = ~(*this)[i];
    }

    return *this;
}

bigint &bigint::negate() &
{
    auto sign = get_sign();

    if (sign == 0)
    {
        return *this;
    }

    int one_int = 1;
    static bigint one(&one_int, 1);

    return sign == 1
           ? invert() += one
           : (*this -= one).invert();
}

bigint bigint::operator-() const
{
    bigint negative(*this);

    return negative.negate();
}

bigint &bigint::operator+=(
        bigint const &summand) &
{
    unsigned int max_digits_count = get_max(get_digits_count(), summand.get_digits_count()) + 1;

    int *result_space = new int[max_digits_count];
    unsigned int extra_digit = 0;

    for (size_t i = 0; i < max_digits_count; ++i)
    {
        result_space[i] = 0;

        auto this_digit = static_cast<bigint const *>(this)->operator[](i);
        auto other_digit = summand[i];

        for (size_t j = 0; j < 2; ++j)
        {
            auto this_half_digit = j == 0
                                   ? get_loword(this_digit)
                                   : get_hiword(this_digit);

            auto other_half_digit = j == 0
                                    ? get_loword(other_digit)
                                    : get_hiword(other_digit);

            auto digits_sum = this_half_digit + other_half_digit + extra_digit;

            extra_digit = digits_sum >> SHIFT;

            result_space[i] += (digits_sum & MASK) << (j * SHIFT);
        }
    }

    init_with(result_space, max_digits_count);

    delete[] result_space;

    return *this;
}

bigint bigint::operator+(
        bigint const &summand) const
{
    bigint result(*this);

    return result += summand;
}

bigint &bigint::operator++()
{
    if (get_sign() == -1)
    {
        return (--negate()).negate();
    }

    size_t digits_count = get_digits_count();
    for (int i = 0; i < digits_count - 1; ++i)
    {
        if (++((*this)[i]) != 0)
        {
            return *this;
        }
    }

    if (++_oldest_digit != INT_MIN)
    {
        return *this;
    }

    if (_other_digits == nullptr)
    {
        _other_digits = new int[2];
        _other_digits[0] = 2;
        _other_digits[1] = _oldest_digit;
        _oldest_digit = 0;

        return *this;
    }

    int *new_array = new int[digits_count + 1];
    memcpy(new_array, _other_digits, sizeof(int) * digits_count);
    ++*new_array;

    delete [] _other_digits;
    _other_digits = new_array;

    (*this)[digits_count - 1] = _oldest_digit;
    _oldest_digit = 0;

    return *this;
}

bigint const bigint::operator++(
        int)
{
    bigint curr(*this);
    ++*this;
    return curr;
}

bigint &bigint::operator-=(
        bigint const &minuend) &
{
    return *this += -minuend;
}

bigint bigint::operator-(
        bigint const &minuend) const
{
    bigint result(*this);

    return result -= minuend;
}

bigint &bigint::operator--()
{
    if (get_sign() == -1)
    {
        return (++negate()).negate();
    }

    if (get_sign() == 0)
    {
        _oldest_digit = -1;
        return *this;
    }

    size_t digits_count = get_digits_count();
    for (int i = 0; i < digits_count; ++i)
    {
        if (--((*this)[i]) != -1)
        {
            break;
        }
    }

    if (_oldest_digit != 0)
    {
        return *this;
    }

    if (get_sign() == 0)
    {
        return *this;
    }

    if (_other_digits[digits_count - 1] != INT_MAX)
    {
        return *this;
    }

    if (get_digits_count() == 2)
    {
        _oldest_digit = _other_digits[1];
        delete[] _other_digits;
        _other_digits = nullptr;

        return *this;
    }

    int *new_array = new int[digits_count - 1];
    memcpy(new_array, _other_digits, sizeof(int) * get_digits_count() - 1);
    --*new_array;

    _oldest_digit = _other_digits[digits_count - 1];

    delete[] _other_digits;
    _other_digits = new_array;

    return *this;
}

bigint const bigint::operator--(
        int)
{
    bigint x = *this;
    --*this;
    return x;
}

bigint &bigint::operator*=(
        bigint const &multiplier) &
{
    if (get_sign() == 0)
    {
        return *this;
    }

    if (multiplier.get_sign() == 0)
    {
        return *this = multiplier;
    }

    // TODO: German should handle multiplication of two negative values o_O

    if (multiplier.get_sign() == -1)
    {
        return (*this *= -multiplier).negate();
    }

    if (get_sign() == -1)
    {
        return (negate() *= multiplier).negate();
    }

    // TODO: Egor Letov should handle multiplying by 1/-1

    int words_multiplication_result_digits[2] = { 0 };
    int digit = 0;
    unsigned int words_multiplication_result_digit = 0;
    bigint const zero(&digit, 1);
    bigint result = zero;

    auto this_digits_count = get_digits_count();
    auto multiplier_digits_count = multiplier.get_digits_count();

    for (size_t i = 0; i < this_digits_count; ++i)
    {
        auto this_digit = (*this)[i];
        auto this_digit_loword = get_loword(this_digit);
        auto this_digit_hiword = get_hiword(this_digit);

        for (size_t j = 0; j < multiplier_digits_count; ++j)
        {
            auto multiplier_digit = multiplier[j];
            auto multiplier_digit_loword = get_loword(multiplier_digit);
            auto multiplier_digit_hiword = get_hiword(multiplier_digit);

            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_loword, multiplier_digit_loword, (i + j) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_loword, multiplier_digit_hiword, (i + j + 1) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_hiword, multiplier_digit_loword, (i + j + 1) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_hiword, multiplier_digit_hiword, (i + j + 2) << 1);
        }
    }

    delete[] _other_digits;
    _other_digits = result._other_digits;
    result._other_digits = nullptr;
    _oldest_digit = result._oldest_digit;

    return *this;
}

bigint bigint::operator*(
        bigint const &multiplier) const
{
    bigint result = *this;

    return result *= multiplier;
}

bigint &bigint::operator/=(
        bigint const &divisor) &
{
    auto result = this->division(divisor);

    return *this = std::move(result.get_german());
}

bigint bigint::operator/(
        bigint const &divisor) const
{
    return this->division(divisor).get_german();
}

bigint &bigint::operator%=(
        bigint const &divisor) &
{
    auto result = this->division(divisor);

    return *this = std::move(result.get_remainder());
}

bigint bigint::operator%(
        bigint const &divisor) const
{
    return this->division(divisor).get_remainder();
}

bigint::division_result bigint::division(
        bigint const &divisor) const
{
    auto this_sign = get_sign();
    auto divisor_sign = divisor.get_sign();

    if (this_sign == 0 && divisor_sign == 0)
    {
        throw mathematical_uncertainty_exception();
    }

    if (divisor_sign == 0)
    {
        throw division_by_zero_exception();
    }

    if (this_sign == 0)
    {
        int value = 0;
        bigint zero(&value, 1);

        return { zero, zero };
    }

    if (this_sign == -1 && divisor_sign == -1)
    {
        return (-*this).division(-divisor);
    }

    if (this_sign == -1)
    {
        // TODO: return
    }

    if (divisor_sign == -1)
    {
        // TODO: return
    }

    int value = 0;
    bigint german(&value, 1);

    value = 1;
    bigint one(&value, 1);

    auto divisor_oldest_value_bit_index = divisor.get_oldest_positive_value_bit_index();
    auto this_copy = *this;

    while (this_copy >= divisor)
    {
        auto this_oldest_value_bit_index = get_oldest_positive_value_bit_index();
        auto divisor_shift = this_oldest_value_bit_index - divisor_oldest_value_bit_index;
        auto shifted_divisor = divisor << divisor_shift;

        if (shifted_divisor > this_copy)
        {
            shifted_divisor >>= 1;
        }

        this_copy -= shifted_divisor;
        // TODO: use |= or set_bit function
        german += (one << divisor_shift);
    }

    return { german, this_copy };
}

int bigint::comparer(bigint const &other) const
{
    int this_sign = get_sign();
    int other_sign = other.get_sign();
    size_t this_digits_count = get_digits_count();
    size_t other_digits_count = other.get_digits_count();

    if ((this_sign == -1) && (other_sign == 1 || other_sign == 0))
    {
        return -1;
    }

    if ((this_sign == 0 || this_sign == 1) && (other_sign == -1))
    {
        return 1;
    }

    if (this_sign == 0 && other_sign == 0)
    {
        return 0;
    }

    if (this_digits_count < other_digits_count)
    {
        return -1;
    }

    if (this_digits_count > other_digits_count)
    {
        return 1;
    }

    bigint this_cpy(*this), other_cpy(other);

    if ((this_sign == -1) && (other_sign == -1))
    {
        this_cpy = -(this_cpy);
        other_cpy = -(other_cpy);
    }

    for (int i = 1; i < this_digits_count; ++i)
    {
        auto this_digit = reinterpret_cast<unsigned int *>(this_cpy._other_digits[i]);
        auto other_digit = reinterpret_cast<unsigned int *>(other_cpy._other_digits[i]);
        if (this_digit != other_digit)
        {
            if (this_digit < other_digit)
            {
                return -1;
            }

            if(this_digit > other_digit)
            {
                return 1;
            }
        }
    }
    auto this_oldest_digit = reinterpret_cast<unsigned int *>(this_cpy._oldest_digit);
    auto other_oldest_digit = reinterpret_cast<unsigned int *>(other_cpy._oldest_digit);

    if (this_oldest_digit > other_oldest_digit)
    {
        return 1;
    }

    if(this_oldest_digit < other_oldest_digit)
    {
        return -1;
    }

    return 0;
}

bool bigint::operator==(
        bigint const &other) const
{
    return (comparer(other) == 0);
}

bool bigint::operator!=(
        bigint const &other) const
{
    return (comparer(other) != 0);
}

bool bigint::operator<(
        bigint const &other) const
{
    return (comparer(other) == -1);
}

bool bigint::operator<=(
        bigint const &other) const
{
    return ((comparer(other) == -1) || (comparer(other) == 0));
}

bool bigint::operator>(
        bigint const &other) const
{
    return (comparer(other) == 1);
}

bool bigint::operator>=(
        bigint const &other) const
{
    return ((comparer(other) == 1) || (comparer(other) == 0));
}

bigint bigint::operator~() const
{

}

bigint &bigint::operator&=(
        bigint const &other) &
{

}

bigint bigint::operator&(
        bigint const &other) const
{

}

bigint &bigint::operator|=(
        bigint const &other) &
{

}

bigint bigint::operator|(
        bigint const &other) const
{

}

bigint &bigint::operator^=(
        bigint const &other) &
{

}

bigint bigint::operator^(
        bigint const &other) const
{

}

bigint &bigint::operator<<=(
        size_t shift) &
{
    if (shift == 0)
    {
        return *this;
    }

    // TODO: bitwise impl
    int const count_of_zeros_to_add = shift / (sizeof(int) << 3);
    shift &= ((sizeof(int) << 3) - 1);

    if (shift != 0)
    {
        int bits_from_previous_digit = 0;
        int bits_for_next_digit = 0;

        for (int i = 0; i != get_digits_count(); ++i)
        {
            bits_for_next_digit = (*this)[i] >> ((sizeof(int) << 3) - shift) /* TODO: & MASK */;
            ((*this)[i] <<= shift) |= bits_from_previous_digit;
            bits_from_previous_digit = bits_for_next_digit;
        }
    }

    // TODO: dObaViT cIfRi V KoNeZ =)
}

bigint bigint::operator<<(
        size_t shift) const
{
    bigint temp = *this;

    return temp <<= shift;
}

bigint &bigint::operator>>=(
        size_t shift) &
{

}

bigint bigint::operator>>(
        size_t shift) const
{
    bigint temp = *this;

    return temp >>= shift;
}

std::ostream &operator<<(
        std::ostream &stream,
        bigint const &value)
{
    auto digits_count = value.get_digits_count();
    for (auto i = 0; i < digits_count; ++i)
    {
        stream << const_cast<bigint &>(value)[i] << ' ';
    }

    return stream;
}

std::istream &operator>>(
        std::istream &stream,
        bigint &value)
{


    return stream;
}

int main()
{
    return 0;
}