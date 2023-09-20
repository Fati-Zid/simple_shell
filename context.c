#include "shell.h"

/**
 * context_init - Initializes a new shell context.
 * Return: A pointer to the created context, or NULL on failure.
 */
context_t *context_init(char *pname)
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

	/* Set process name */
	ctx->pname = pname;

	/* Init status */
	ctx->status = 0;
	ctx->error_count = 0;
	return (ctx);
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
