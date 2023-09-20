#include "shell.h"

/**
 * context_init - Initializes a new shell context.
 * Return: A pointer to the created context, or NULL on failure.
 */
context_t *context_init(void)
{
	/* Create context */
	context_t *ctx = (context_t *)malloc(sizeof(context_t));
	if (ctx == NULL)
		return (NULL);
	_memset((void *)ctx, 0, sizeof(context_t));

	/* Init command */
	ctx->cmd = (command_t *)malloc(sizeof(command_t));
	if (ctx->cmd == NULL)
	{
		free(ctx);
		return (NULL);
	}
	_memset((void *)ctx->cmd, 0, sizeof(command_t));

	/* Set interactive mode */
	ctx->isatty = (int)(isatty(STDIN_FILENO) > 0);

	/* Init status */
	ctx->status = 0;
	return (ctx);
}

/**
 * command_free - Frees memory allocated for the command attributes.
 * @ctx: The shell context containing the command.
 */
void command_free(context_t *ctx)
{
    command_t *cmd = ctx->cmd;
	if (cmd->buff != NULL)
	{
		free(cmd->buff);
		cmd->buff = NULL;
	}

	if (cmd->argv != NULL)
	{
		arg_free(cmd->argv);
		cmd->argv = NULL;
	}

	if (cmd->name != NULL)
	{
		free(cmd->name);
		cmd->name = NULL;
	}

	cmd->argc = 0;
}

void arg_free(char **argv)
{
	char **a = argv;

	if (!argv)
		return;
	while (*argv)
		free(*argv++);
	free(a);
}

/**
 * context_free - Frees memory allocated for the entire context.
 * @ctx: The shell context to be freed.
 */
void context_free(context_t *ctx)
{
	list_free(&(ctx->env));
	free(ctx->cmd);
	free(ctx);
}
