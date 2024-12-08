#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MSB_NUMBER ((sizeof(int) * 8) - 1)
#define MSB_MASK (1 << MSB_NUMBER)

struct DIV_RESULT
{
	unsigned quotient;
	unsigned remainder;
};

struct DIV_RESULT sdiv(unsigned dividend, unsigned divisor);
struct DIV_RESULT udiv(unsigned dividend, unsigned divisor);

int main()
{
	int dividend, divisor;
	puts("Enter zero for divisor to end program, For example, Operation: 15/0");

	while (1)
	{
		printf("\nOperation: ");
		fflush(stdin);
		scanf("%i / %i", &dividend, &divisor);
		if (!divisor)
			break;
		struct DIV_RESULT div = sdiv(dividend, divisor);
		printf("\n(SDIV)\nQuotient = %i\nRemainder = %u\n", 
				div.quotient, div.remainder);

		div = udiv(dividend, divisor);
		printf("\n(UDIV)\nQuotient = %u\nRemainder = %u\n", 
				div.quotient, div.remainder);
	}

	puts("Exit success!");
	return 0;
}

struct DIV_RESULT sdiv(unsigned dividend, unsigned divisor)
{
	struct DIV_RESULT result = {0, 0};
	int counter = 0;
	if(!divisor)
		return result;

	/* store resulting signs, then convert all to unsigned */
	int sign = 0;
	if (divisor & MSB_MASK)
	{
		divisor = ~divisor + 1;
		sign = !sign;
	}
	if (dividend & MSB_MASK)
	{
		dividend = ~dividend + 1;
		sign = !sign;
	}

	while(dividend >= divisor) 
	{
		divisor <<= 1;
		counter++;
	}
	divisor >>= 1;

	while (counter--)
	{
		result.quotient <<= 1;
		if(dividend >= divisor) 
		{
			dividend -= divisor;
			result.quotient |= 1;
		}
		divisor >>= 1;
	}

	if(sign)
		result.quotient = ~result.quotient + 1;
	result.remainder = dividend;
	return result;
}

struct DIV_RESULT udiv(unsigned dividend, unsigned divisor)
{
	struct DIV_RESULT result = {0, 0};
	int counter;
	if(!divisor)
		return result;

	if (dividend & MSB_MASK)
	{
		counter = 1;
		while(!(MSB_MASK & divisor))
		{
			divisor <<= 1;
			counter++;
		}
	}

	else
	{
		counter = 0;
		while(dividend >= divisor) 
		{
			divisor <<= 1;
			counter++;
		}
		divisor >>= 1;
	}

	while (counter--)
	{
		result.quotient <<= 1;
		if(dividend >= divisor) 
		{
			dividend -= divisor;
			result.quotient |= 1;
		}
		divisor >>= 1;
	}

	result.remainder = dividend;
	return result;
}
