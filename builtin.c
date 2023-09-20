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
			_eputsln(ctx->cmd->argv[1]);
			return (1);
		}
		ctx->status = exitcode;
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

int envsetfn(context_t *ctx)
{
	command_t *cmd = ctx->cmd;
	if (cmd->argc != 3)
	{
		_eputsln("Incorrect number of arguements");
		return (1);
	}
	if (envset(ctx, cmd->argv[1], cmd->argv[2]))
		return (1);
	return (0);
}

int envunsetfn(context_t *ctx)
{
	int i;

	if (ctx->cmd->argc == 1)
	{
		_eputsln("Too few arguements.");
		return (1);
	}
	for (i = 1; i <= ctx->cmd->argc; i++)
		envunset(ctx, ctx->cmd->argv[i]);

	return (0);
}