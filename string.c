#include "shell.h"

/**
 * _strlen - Calculate the length of a string.
 * @str: The input string.
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
	size_t i = 0;

	if (str == NULL)
		return (0);

	while (*str++)
		i++;
	return (i);
}

char *_strdup(const char *src)
{
	char *str;
	size_t size = _strlen(src) + 1;

	str = (char *) malloc(size);
	if (str) {
		_memcpy(str, src, size);
	}
	return str;
}

/**
 * _strcmp - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 * Return: 0 if strings are equal, negative if str1 < str2, positive if str1 > str2.
 */
unsigned int _strcmp(const char *str1, const char *str2)
{
	while(*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

