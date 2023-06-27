#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the pointer's value of a variable
 * @types: array of arguments
 * @buffer:  array to handle print
 * @flags:  meadures active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & O_ZERO) && !(flags & O_MINUS))
		padd = '0';
	if (flags & O_PLUS)
		extra_c = '+', length++;
	else if (flags & O_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: array of arguments
 * @buffer: array to handle print
 * @flags:  measures active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int z = 0, offlay = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[z] != '\0')
	{
		if (is_printable(str[z]))
			buffer[z + offlay] = str[z];
		else
			offlay += append_hexa_code(str[z], buffer, z + offlay);

		z++;
	}

	buffer[z + offlay] = '\0';

	return (write(1, buffer, z + offlay));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: array of arguments
 * @buffer: array to handle print
 * @flags:  measures active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int z, sum = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (z = 0; str[z]; z++)
		;

	for (z = z - 1; z >= 0; z--)
	{
		char k = str[z];

		write(1, &k, 1);
		sum++;
	}
	return (sum);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13string.
 * @types: array of arguments
 * @buffer: array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int z, k;
	int sum = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (z = 0; str[z]; z++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[z])
			{
				x = out[k];
				write(1, &x, 1);
				sum++;
				break;
			}
		}
		if (!in[k])
		{
			x = str[z];
			write(1, &x, 1);
			sum++;
		}
	}
	return (sum);
}

