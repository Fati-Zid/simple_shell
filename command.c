#include "shell.h"

/**
 * command_parse: function that ...
 * @ctx: The shell context containing the command.
 * Return: 1 on success and -1 on failure
 */

unsigned int command_parse(context_t *ctx)
{
	command_t *cmd = ctx->cmd;

	if (cmd->buff == NULL)
		return (-1);

	cmd->argv = strtow(cmd->buff, &(cmd->argc), " \t");

	if (!cmd->argv)
	{
		cmd->argv = (char **)malloc(sizeof(char *) * 2);
		if (cmd->argv == NULL)
			return (-1);
		
		_memset((void *)cmd->argv, 0, sizeof(char *) * 2);
		cmd->argv[0] = _strdup(cmd->buff, 0, -1);
		cmd->argv[1] = NULL;
		cmd->argc = 1;

	}

	cmd->name = _strdup(cmd->argv[0], 0, -1);
	return (1);
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

	if(cmd->path != NULL)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	cmd->argc = 0;
}

/**
 * arg_free: function that free argv
 * @argv: array of argument
 * Return: nothing
 */

void arg_free(char **argv)
{
	char **a = argv;

	if (!argv)
		return;
	while (*argv)
		free(*argv++);
	free(a);
}
