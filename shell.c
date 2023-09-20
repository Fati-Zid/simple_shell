#include "shell.h"

/**
 * hsh - Executes the main shell loop.
 * @ctx: The shell context.
 */
void hsh(context_t *ctx)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -3)
	{
		if (ctx->isatty)
			_puts("($) ");

		r = read_input(ctx);

		if (r > 0)
		{
			_putsln(ctx->cmd->buff);
			ret = exec_builtin(ctx);
		}
		else if (r == -1 && ctx->isatty)
		{
			_puts("\n");
		}
		command_free(ctx);
	}
}

/**
 * exec_builtin - Executes a built-in command if available.
 * @ctx: The shell context.
 * Return: The return value of the built-in command, -1 if not found.
 */
int exec_builtin(context_t *ctx)
{
	int i, ret = -1;
	builtinfun_t table[] = {
		{"exit", exitfn},
		{"env", envfn},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
	{
		if (_strcmp(ctx->cmd->buff, table[i].type) == 0)
		{
			ret = table[i].func(ctx);
			break;
		}
	}
	return (ret);
}
