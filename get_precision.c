#include "main.h"

/**
 * get_precision - measures the precision for printing
 * @format: Formatted string in which to print the lists
 * @i: array of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_z = *i + 1;
	int precision = -1;

	if (format[curr_z] != '.')
		return (precision);

	precision = 0;

	for (curr_z += 1; format[curr_z] != '\0'; curr_z++)
	{
		if (is_digit(format[curr_z]))
		{
			precision *= 10;
			precision += format[curr_z] - '0';
		}
		else if (format[curr_z] == '*')
		{
			curr_z++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_z - 1;

	return (precision);
}

