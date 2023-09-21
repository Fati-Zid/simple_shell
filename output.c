#include "shell.h"

/**
 * _puts - Writes a string to the standard output.
 * @str: Pointer to the string to be written.
 */
void _puts(const char *str)
{
	write(1, str, _strlen(str));
}

void _putsln(const char *str)
{
	_puts(str);
	_puts("\n");
}

void _putserror(context_t *ctx, const char *error)
{
	_puts(ctx->pname);
	_puts(": 1: ");
	_puts(ctx->cmd->name);
	_puts(": ");
	_puts(error);
}
