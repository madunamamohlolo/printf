#include "main.h"

/**
 * get_flags - measures active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a coefficience.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	int k, curr_z;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {O_MINUS, O_PLUS, O_ZERO, O_HASH, O_SPACE, 0};

	for (curr_z = *i + 1; format[curr_z] != '\0'; curr_z++)
	{
		for (k = 0; FLAGS_CH[k] != '\0'; k++)
			if (format[curr_z] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}

		if (FLAGS_CH[k] == 0)
			break;
	}

	*i = curr_z - 1;

	return (flags);
}

