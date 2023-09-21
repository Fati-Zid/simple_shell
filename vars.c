#include "shell.h"

/**
 * replace_vars - Replaces environment variable
 * references with their values in command arguments.
 * @ctx: The shell context containing the
 * command with arguments to process.
 *
 * Return: 0 on success, or appropriate error code on failure.
 */
int replace_vars(context_t *ctx)
{
	int i = 0;
	list_t *node;
	char **argv = ctx->cmd->argv;
	int argc = ctx->cmd->argc;

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '$' || !argv[i][1])
			continue;

		if (!_strcmp(argv[i], "$?"))
		{
			replace_string(&(argv[i]),
					_strdup(_itoa(ctx->status, 10, 0), 0, -1));
			continue;
		}
		if (!_strcmp(argv[i], "$$"))
		{
			replace_string(&(argv[i]),
					_strdup(_itoa(getpid(), 10, 0), 0, -1));
			continue;
		}
		node = node_starts_with(ctx->env, &argv[i][1], '=');
		if (node)
		{
			replace_string(&(argv[i]),
					_strdup(_strchr(node->data, '=') + 1, 0 , -1));
			continue;
		}
		replace_string(&argv[i], _strdup("", 0, -1));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
