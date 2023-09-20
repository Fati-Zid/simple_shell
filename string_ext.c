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