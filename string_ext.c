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

#include "shell.h"

/**
 * is_white_space - Check if a character is whitespace.
 * @c: The character to check.
 * Return: 1 if the character is whitespace, 0 otherwise.
 */
int is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * first_position - Find the index of the first
 * non-whitespace character in a string.
 * @str: The string to search.
 * Return: The index of the first non-whitespace character.
 */
int first_position(char const *str)
{
	int i = 0;

	while (is_white_space(str[i]))
		i += 1;
	return (i);
}

/**
 * last_position - Find the index of the last
 * non-whitespace character in a string.
 * @str: The string to search.
 * Return: The index of the last non-whitespace character.
 */
int last_position(char const *str)
{
	int i = _strlen(str) - 1;

	while (is_white_space(str[i]))
		i -= 1;
	return (i);
}

/**
 * _strtrim - Trim leading and trailing whitespace from a string.
 * @str: The input string.
 * @len: Pointer to store the length of the trimmed string.
 * Return: A dynamically allocated string with trimmed content.
 *         NULL if the input string is NULL or empty after trimming.
 */
char *_strtrim(char const *str, ssize_t *len)
{
	char *trim = NULL;
	int start, end;

	if (str != NULL)
	{
		start = first_position(str);
		end = last_position(str);
		*len = 0;
		if (end > start)
		{
			*len = (ssize_t)(end - start + 1);
			trim = _strdup(str, start, end);
		}
	}
	return (trim);
}
