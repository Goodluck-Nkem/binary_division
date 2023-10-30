#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MSB_NUMBER ((sizeof(uint32_t) * 8) - 1)
#define MSB_MASK (1 << MSB_NUMBER)

uint32_t binary_div(uint32_t dividend, uint32_t divisor);

int main()
{
    uint32_t dividend, divisor;
    puts("Enter zero for divisor to end program, For example, Operation: 15/0");

    while (1)
    {
        printf("Operation: ");
        scanf("%u / %u", &dividend, &divisor);
        if (!divisor)
            break;
        printf("Quotient = %i\n", binary_div(dividend, divisor));
    }

    puts("Exit success!");
    return 0;
}

uint32_t binary_div(uint32_t dividend, uint32_t divisor)
{
    uint32_t quotient = 0;
    uint32_t dividend_shift, divisor_msb = MSB_NUMBER, dividend_msb = MSB_NUMBER; // starting from MSB
    uint32_t temp_divisor = divisor;
    uint32_t temp_dividend = dividend;
    uint32_t new_dividend;
    if (!divisor || divisor > dividend)
        return 0;

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
        quotient |= 1;
    // new_dividend is our remainder
    return quotient;
}
