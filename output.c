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
 * _putsln - Writes a string and break line to the standard output.
 * @str: Pointer to the string to be written.
 */
void _putsln(const char *str)
{
	_puts(str);
	_pust("\n");
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
 * _putserror - ....
 * @error: ...
 * @ctx: the shell context
 * Return: ...
 */
void _putserror(context_t *ctx, const char *error, int no_count)
{
	ctx->error_count++;
	_eputs(ctx->pname);
	_eputs(": ");
	if(!no_count)
	{
		_eputs(_itoa(ctx->error_count, 10, 0));
		_eputs(": ");
	}
	_eputs(ctx->cmd->name);
	_eputs(": ");
	if(no_count)
	{
		_eputs(ctx->cmd->argv[1]);
		_eputs(": ");
	}
	_eputs(error);
}
