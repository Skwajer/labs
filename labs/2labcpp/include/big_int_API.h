#ifndef INC_2LABCPP_BIG_INT_API_H
#define INC_2LABCPP_BIG_INT_API_H

#ifndef COURSE1_CPP_RGU_bigint_H
#define COURSE1_CPP_RGU_bigint_H

#include <corecrt.h>
#include <iostream>

class bigint final
{

public:

    class mathematical_uncertainty_exception:
            std::exception
    {

    };

    class division_by_zero_exception:
            std::exception
    {

    };

private:

    static unsigned int get_max(
            unsigned int first,
            unsigned int second) noexcept
    {
        return first > second
               ? first
               : second;
    }

private:

    static constexpr unsigned int HALF_DIGIT_SHIFT = (sizeof(int) << 2);

    static constexpr unsigned int SHIFT = (sizeof(int) << 2);

    static constexpr unsigned int MASK = (1 << SHIFT) - 1;

private:

    static unsigned int get_loword(
            unsigned int value)
    {
        return value & MASK;
    }

    static unsigned int get_hiword(
            unsigned int value)
    {
        return value >> SHIFT;
    }

private:

    static void addition_for_multiplication(
            bigint &summand,
            int *words_multiplication_result_digits,
            unsigned int this_half_digit,
            unsigned int multiplier_half_digit,
            unsigned int shift_in_half_digits)
    {
        unsigned int words_multiplication_result_digit = this_half_digit * multiplier_half_digit;
        *words_multiplication_result_digits = *reinterpret_cast<int *>(&words_multiplication_result_digit);
        summand += (bigint(words_multiplication_result_digits, 2) << (HALF_DIGIT_SHIFT * shift_in_half_digits));
    }

    int get_oldest_positive_value_bit_index() const noexcept
    {
        auto digits_count = get_digits_count();

        auto oldest_digit = _oldest_digit;
        int oldest_digit_oldest_bit_index = 0;
        while (oldest_digit != 0)
        {
            oldest_digit >>= 1;
            ++oldest_digit_oldest_bit_index;
        }
        return oldest_digit_oldest_bit_index + ((int)digits_count - 1) * (int)(sizeof(int) << 3) - 1;
    }

private:

    int _oldest_digit;
    int *_other_digits;

private:

    void dispose();

    void copy_from(
            bigint const &other);

    void move_from(
            bigint &&other);

public:

    ~bigint() noexcept;

    bigint(
            bigint const &other);

    bigint(
            bigint &&other) noexcept;

    bigint &operator=(
            bigint const &other);

    bigint &operator=(
            bigint &&other) noexcept;

private:

    bigint &init_with(
            int const *digits_array,
            size_t digits_count);

public:

    bigint(
            int const *digits,
            size_t digits_count);

    bigint(
            char const *string_representation,
            size_t base);

private:

    int comparer(bigint const &) const;

    inline int get_sign() const noexcept;

    inline size_t get_digits_count() const noexcept;

    unsigned int operator[](
            size_t index) const noexcept;

    int &operator[](
            size_t index);

    bigint &negate() &;

    bigint& invert() &;

public:

    bigint operator-() const;

    bigint &operator+=(
            bigint const &summand) &;

    bigint operator+(
            bigint const &summand) const;

    bigint &operator++();

    bigint const operator++(
            int);

    bigint &operator-=(
            bigint const &minuend) &;

    bigint operator-(
            bigint const &minuend) const;

    bigint &operator--();

    bigint const operator--(
            int);

    bigint &operator*=(
            bigint const &multiplier) &;

    bigint operator*(
            bigint const &multiplier) const;

    bigint &operator/=(
            bigint const &divisor) &;

    bigint operator/(
            bigint const &divisor) const;

    bigint &operator%=(
            bigint const &divisor) &;

    bigint operator%(
            bigint const &divisor) const;

    class division_result final
    {

    private:

        bigint *_german;
        bigint *_remainder;

    public:

        division_result(
                bigint const &german,
                bigint const &remainder):
                _german(new bigint(german)),
                _remainder(new bigint(remainder))
        {

        }

    public:

        // TODO: implement rule of 5

        ~division_result()
        {
            delete _german; _german = nullptr;
            delete _remainder; _remainder = nullptr;
        }

    public:

        bigint get_german() const
        {
            return *_german;
        }

        bigint get_remainder() const
        {
            return *_remainder;
        }

    };

    division_result division(
            bigint const &divisor) const;

public:

    bool operator==(
            bigint const &other) const;

    bool operator!=(
            bigint const &other) const;

public:

    bool operator<(
            bigint const &other) const;

    bool operator<=(
            bigint const &other) const;

    bool operator>(
            bigint const &other) const;

    bool operator>=(
            bigint const &other) const;

public:

    bigint operator~() const;

    bigint &operator&=(
            bigint const &other) &;

    bigint operator&(
            bigint const &other) const;

    bigint &operator|=(
            bigint const &other) &;

    bigint operator|(
            bigint const &other) const;

    bigint &operator^=(
            bigint const &other) &;

    bigint operator^(
            bigint const &other) const;

    bigint &operator<<=(
            size_t shift) &;

    bigint operator<<(
            size_t shift) const;

    bigint &operator>>=(
            size_t shift) &;

    bigint operator>>(
            size_t shift) const;

public:

    friend std::ostream &operator<<(
            std::ostream &stream,
            bigint const &value);

    friend std::istream &operator>>(
            std::istream &stream,
            bigint &value);

};

#endif //COURSE1_CPP_RGU_bigint_H

#endif //INC_2LABCPP_BIG_INT_API_H
