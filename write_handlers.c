#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Printss a string
 * @c: types of char.
 * @buffer: storage array to handle print
 * @flags:  evaluate active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int z = 0;
	char mike = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & O_ZERO)
		mike = '0';

	buffer[z++] = c;
	buffer[z] = '\0';

	if (width > 1)
	{
		buffer[BUFF - 1] = '\0';
		for (z = 0; z < width - 1; z++)
			buffer[BUFF - z - 2] = mike;

		if (flags & O_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF - z - 1], width - 1));
		else
			return (write(1, &buffer[BUFF - z - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a char
 * @is_negative: Listaa of arguments
 * @ind: strings types.
 * @buffer: storage array to handle print
 * @flags:  evaluate active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF - ind - 1;
	char mike = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & O_ZERO) && !(flags & O_MINUS))
		mike = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & O_PLUS)
		extra_ch = '+';
	else if (flags & O_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, mike, extra_ch));
}

/**
 * write_num - itemise a number using a bufffer
 * @ind: value at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int z, mike = 1;

	if (prec == 0 && ind == BUFF - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (z = 1; z < width - length + 1; z++)
			buffer[z] = padd;
		buffer[z] = '\0';
		if (flags & O_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], z - 1));
		}
		else if (!(flags & O_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], z - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & O_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--mike] = extra_c;
			return (write(1, &buffer[mike], z - mike) +
				write(1, &buffer[ind], length - (1 - mike)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - an unsigned number
 * @is_negative: value indicating if the num is negative
 * @ind: number at which the number starts in the buffer
 * @buffer: Array of chararcters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF - ind - 1, z = 0;
	char mike = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		mike = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & O_ZERO) && !(flags & O_MINUS))
		mike = '0';

	if (width > len)
	{
		for (z = 0; z < width - len; z++)
			buffer[z] = mike;

		buffer[z] = '\0';

		if (flags & O_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], z));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], z) + write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - a memory address
 * @buffer: Arrays of characters
 * @ind: number at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int z;

	if (width > length)
	{
		for (z = 3; z < width - length + 3; z++)
			buffer[z] = padd;
		buffer[z] = '\0';
		if (flags & O_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], z - 3));
		}
		else if (!(flags & O_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], z - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & O_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], z - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF - ind - 1));
}



