#include "shell.h"

/**
 * _starts_with - Check if a string starts with a given substring.
 * @haystack: The string to search in.
 * @needle: The substring to check for.
 * Return: Pointer to the remaining characters if found, NULL otherwise.
 */
char *_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * is_white_space - Check if a string is whitespace.
 * @str: The string to check.
 * Return: 1 if the string is whitespace, 0 otherwise.
 */
int is_white_space(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
