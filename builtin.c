#include "shell.h"

/**
 * exitfn - Handles exit functionality.
 * @ctx: The shell context.
 * Return: The exit status.
 */
int exitfn(context_t *ctx)
{
	int exitcode;
	(void)ctx;
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
		return (0);
	return (1);
}