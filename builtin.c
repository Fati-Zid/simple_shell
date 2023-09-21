#include "shell.h"

/**
 * exitfn - Handles exit functionality.
 * @ctx: The shell context.
 * Return: The exit status.
 */
int exitfn(context_t *ctx)
{
	(void)ctx;
	if (ctx->cmd->argv[1])
	{
		exitcheck = _erratoi(ctx->cmd->argv[1]);
		if (exitcheck == -1)
		{
			_putserror(ctx, "Illegal number: ");
			_putsln(ctx->cmd->argv[1]);
			return (1);
		}
		ctx->status = exitcheck;
	}
	return (-3);
}

/**
 * envfn - Prints the environment.
 * @ctx: The shell context.
 * Return: Always 0.
 */
int envfn(context_t *ctx)
{
	list_t *h = ctx->env;

	while (h != NULL)
	{
		_putsln(h->data ? h->data : "(nil)");
		h = h->next;
	}

	return (0);
}