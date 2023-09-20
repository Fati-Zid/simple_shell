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

void _eputs(const char *str)
{
    write(2, str, _strlen(str));
}

void _eputsln(const char *str)
{
    _eputs(str);
    _eputs("\n");
}

void _putserror(context_t *ctx, const char *error)
{
    _eputs(ctx->pname);
	_eputs(": 1: ");
    _eputs(ctx->cmd->name);
    _eputs(": ");
    _eputs(error);
}