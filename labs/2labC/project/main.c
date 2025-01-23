#include <stdio.h>
#include <stdlib.h>

int binary_plus(
        int a,
        int b)
{
    int carry;

    while (b != 0)
    {
        carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }

    return a;
}

int binary_minus(
        int a,
        int b)
{
    return binary_plus(a, binary_plus(~b, 1));
}

int convert_to_base_2r(
        unsigned int num,
        unsigned int r,
        char* output,
        size_t output_size)
{
    int i;
    unsigned int base, digit, index = 0, temp_num = num;
    size_t required_digits = 0;
    char temp;

    if (r < 1 || r > 5)
    {
        return 1;
    }

    base = (1 << r);
    base = (unsigned int)binary_minus((int)base, 1);

    do
    {
        /*++required_digits*/ required_digits = (size_t)binary_plus((int)required_digits, 1);
        temp_num >>= r;
    }
    while (temp_num);

    if (required_digits >= output_size)
    {
        return 2;
    }

    if (num == 0)
    {
        output[index] = '0';
        index = (unsigned int)binary_plus((int)index, 1);
    }
    else
    {
        while (num)
        {
            digit = num & (base);

            output[index] = (digit < 10)
                            ? /*'0' + digit*/ (char)binary_plus((int)'0', (int)digit)
                            : /*'A' + (digit - 10)*/ (char)binary_plus((int)'A', binary_minus((int)digit, 10));

            num >>= r;
            index = (unsigned int)binary_plus((int)index, 1);
        }
    }

    for (i = 0; i < index >> 1; /*i++*/  i = binary_plus(i, 1))
    {
        temp = output[i];
        output[i] = output[/*index - i - 1*/ binary_minus((int)index, binary_plus(i, 1))];
        output[/*index - i - 1*/ binary_minus((int)index, binary_plus(i, 1))] = temp;
    }

    output[index] = 0;

    return 0;
}

int main()
{
    unsigned int num;
    unsigned int r;
    char output[33];

    printf("Enter the number to convert: ");

    if (scanf("%u", &num) != 1)
    {
        printf("\nError reading the number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the value of r (from 1 to 5): ");

    if (scanf("%u", &r) != 1)
    {
        printf("\nError reading the value of r.\n");

        return EXIT_FAILURE;
    }

    switch (convert_to_base_2r(num, r, output, sizeof(output)))
    {
        case 0:
            printf("The number %u in base 2^%u: %s\n", num, r, output);
            break;

        case 1:
            printf("\nInvalid value for r!\n");
            break;

        case 2:
            printf("\nNot enough space in output str!\n");
            break;

        default:
            printf("\nUnknown error 000000000_________oooooooooo\n");
            break;
    }

    return EXIT_SUCCESS;
}