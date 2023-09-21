#include "shell.h"

/**
 * _erratoi - function ...
 * @s: ....
 * Return: integer
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
