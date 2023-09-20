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
		}
		else if (r == -1 && ctx->isatty)
		{
			_puts("\n");
		}
		command_free(ctx);
	}
}