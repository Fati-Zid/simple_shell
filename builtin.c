#include "shell.h"

/**
 * exitfn - Handles exit functionality.
 * @ctx: The shell context.
 * Return: The exit status.
 */
int exitfn(context_t *ctx)
{
	int exitcode;

	if (ctx->cmd->argv[1])
	{
		exitcode = _erratoi(ctx->cmd->argv[1]);
		if (exitcode == -1)
		{
			_putserror(ctx, "Illegal number: ");
			_eputs(ctx->cmd->argv[1]);
			_eputs("\n");
			ctx->status = 2;
			return (1);
		}
		ctx->status = exitcode;
	}
	return (-3);
}
