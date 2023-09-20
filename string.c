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

/**
 * _strdup - Duplicate a portion of a string into a new buffer.
 * @str: The original string.
 * @start: The starting index of the portion.
 * @stop: The stopping index of the portion.
 * Return: Pointer to the newly allocated buffer with duplicated content.
 */
char *_strdup(const char *str, int start, int stop)
{
	int length, i, k;
	char *buff = NULL;
	int toend = stop == -1;

	if (str == NULL)
		return (NULL);

	if (toend)
	{
		length = _strlen(str);
		stop = length - 1;
	} else
	{
		length = (stop - start) + 1;
	}

	buff = (char *)malloc((length + 1) * sizeof(char));

	if (!buff)
		return (NULL);

	for (k = 0, i = start; i <= stop; i++, k++)
		buff[k] = str[i];

	buff[k] = '\0';

	return (buff);
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

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strcat - Concatenate two strings.
 * @str1: The first string.
 * @str2: The second string.
 * Return: Pointer to the destination string.
 */
char *_strcat(char **str1, char *str2)
{
	char *ret;
	int newsize, i = 0, k = 0;

	if (!*str1 || !str2)
		return (NULL);

	newsize = _strlen(*str1) + _strlen(str2);
	ret = (char *)malloc((newsize + 1) * sizeof(char));

	if (!ret)
		return (NULL);

	while ((*str1)[i] != '\0')
	{
		ret[i] = (*str1)[i];
		i++;
	}
	while (str2[k] != '\0')
	{
		ret[i] = str2[k];
		i++;
		k++;
	}
	ret[i] = '\0';
	free(*str1);
	*str1 = ret;
	return (ret);
}

