#include "main.h"

/**
 * get_size - measures the size to cast the argument
 * @format: Formatted string in which to print the list
 * @i: array of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curr_z = *i + 1;
	int len = 0;

	if (format[curr_z] == 'l')
		len = L_LONG;
	else if (format[curr_z] == 'h')
		len = L_SHORT;

	if (len == 0)
		*i = curr_z - 1;
	else
		*i = curr_z;

	return (len);
}

