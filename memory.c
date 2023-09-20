#include "shell.h"

/**
 * memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @c: Value to be set.
 * @n: Number of bytes to be set.
 * Return: Pointer to the memory area @s.
 */
char *_memset(char *s, char c, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}

void _memcpy(char *dest, const char *src, size_t n) 
{
	for (int i=0; i<n; i++) 
		dest[i] = src[i]; 
} 