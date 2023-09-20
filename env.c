#include "shell.h"

/**
 * envset - Populates the shell environment list.
 * @ctx: The shell context.
 * Return: The number of environment variables.
 */
size_t envset(context_t *ctx)
{
	list_t *env = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		list_push(&env, environ[i]);
	ctx->env = env;
	return (i);
}