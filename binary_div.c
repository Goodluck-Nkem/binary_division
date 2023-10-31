#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MSB_NUMBER ((sizeof(int) * 8) - 1)
#define MSB_MASK (1 << MSB_NUMBER)

struct DIV_RESULT
{
    int quotient, remainder;
};

struct DIV_RESULT binary_div(int dividend, int divisor);

int main()
{
    int dividend, divisor;
    puts("Enter zero for divisor to end program, For example, Operation: 15/0");

    while (1)
    {
        printf("Operation: ");
        scanf("%i / %i", &dividend, &divisor);
        if (!divisor)
            break;
        struct DIV_RESULT div = binary_div(dividend, divisor);
        printf("Quotient = %i\nRemainder = %i\n", div.quotient, div.remainder);
        /* confirm dividend = (divisor * quotient) + remainder */
    }

    puts("Exit success!");
    return 0;
}

struct DIV_RESULT binary_div(int dividend, int divisor)
{
    /* store resulting signs, then convert all to unsigned */
    int quotient_sign = (divisor < 0 ^ dividend < 0) ? -1 : 1, remainder_sign = 1;
    if (divisor < 0)
        divisor *= -1;
    if (dividend < 0)
    {
        remainder_sign = -1;
        dividend *= -1;
    }

    struct DIV_RESULT res = {0, 0};
    int quotient = 0;
    int dividend_shift, divisor_msb = MSB_NUMBER, dividend_msb = MSB_NUMBER; // starting from MSB
    int temp_divisor = divisor;
    int temp_dividend = dividend;
    int new_dividend;

    if (!divisor)
        return res;
    if (divisor > dividend)
    {
        res.remainder = dividend;
        return res;
    }

    while ((temp_divisor & MSB_MASK) == 0)
    {
        temp_divisor <<= 1, divisor_msb--;
    }
    while ((temp_dividend & MSB_MASK) == 0)
    {
        temp_dividend <<= 1,
            dividend_msb--;
    }

    dividend_shift = dividend_msb - divisor_msb;
    printf("number of dividend shifts = %i\n", dividend_shift);

    new_dividend = dividend >> dividend_shift;
    printf("new_dividend = %i,\tno shift yet\n", new_dividend);
    while (dividend_shift--)
    {
        quotient <<= 1;
        if (new_dividend >= divisor)
        {
            new_dividend -= divisor;
            quotient |= 1;
        }
        new_dividend = (new_dividend << 1) | ((dividend >> dividend_shift) & 1);
        printf("new_dividend = %i,\tdividend_shift = %i\n", new_dividend, dividend_shift);
    }
    quotient <<= 1;
    if (new_dividend >= divisor)
    {
        new_dividend -= divisor;
        quotient |= 1;
    }

    // we have our quotient, then new_dividend is our remainder
    res.quotient = quotient * quotient_sign;
    res.remainder = new_dividend * remainder_sign;
    return res;
}
