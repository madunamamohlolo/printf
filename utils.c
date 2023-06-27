#include "main.h"

/**
 * is_printable - calculate if a char is printable
 * @c: Char to be calculated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to be stored
 * @buffer: list of chars.
 * @i: number at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_in[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_in[ascii_code / 16];
	buffer[i] = map_in[ascii_code % 16];

	return (3);
}

/**
 * is_digit - examine if a char is a number
 * @c: calculated char
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a digit to the configured size
 * @num: Number to be counted.
 * @size: Number indicating the type to be counted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == L_LONG)
		return (num);
	else if (size == L_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - count a number to the specified size
 * @num: digit to be casted
 * @size: digit that showing the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == L_LONG)
		return (num);
	else if (size == L_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

