
#include "main.h"

/**
 * get_width - evaluate the width for printing
 * @format: arranged string in which to print the list.
 * @i: List of arguments to be printed.
 * @list: array of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int z;
	int len = 0;

	for (z = *i + 1; format[z] != '\0'; z++)
	{
		if (is_digit(format[z]))
		{
			len *= 10;
			len += format[z] - '0';
		}
		else if (format[z] == '*')
		{
			z++;
			len = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = z - 1;

	return (len);
}

