#include "shell.h"

/**
 * _puts - Writes a string to the standard output.
 * @str: Pointer to the string to be written.
 */
void _puts(const char *str)
{
	write(1, str, _strlen(str));
}

void _eputs(const char *str)
{
    write(2, str, _strlen(str));
}

void _putsa(int v)
{
    int r;
    while (v != 0) {
        r = v % 10;
        v = v / 10;
        _puts('0' + r);
    } 
}

void _putserror(context_t *ctx, const char *error)
{
    ctx->error_count++;
    _eputs(ctx->pname);
	_eputs(": ");
    _putsa(ctx->error_count);
    _eputs(": ");
    _eputs(ctx->cmd->name);
    _eputs(": ");
    _eputs(error);
}