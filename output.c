#include "shell.h"

/**
 * _puts - Writes a string to the standard output.
 * @str: Pointer to the string to be written.
 */
void _puts(const char *str)
{
	write(1, str, _strlen(str));
}

/**
 * _eputs - ....
 * @str: ...
 * Return: ...
 */
void _eputs(const char *str)
{
	write(2, str, _strlen(str));
}

/**
 * _eputsa - ....
 * @v: ...
 * Return: ...
 */

void _eputsa(int v)
{
	char str[100];
	int r, i = 0;

	while (v != 0)
	{
		r = v % 10;
		v = v / 10;
		str[i] = (char)('0' + r);
		i++;
	}
	str[i] = '\0';
	_eputs(str);
}

/**
 * _putserror - ....
 * @error: ...
 * @ctx: the shell context
 * Return: ...
 */
void _putserror(context_t *ctx, const char *error)
{
	ctx->error_count++;
	_eputs(ctx->pname);
	_eputs(": ");
	_eputsa(ctx->error_count);
	_eputs(": ");
	_eputs(ctx->cmd->name);
	_eputs(": ");
	_eputs(error);
}
