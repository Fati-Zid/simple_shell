#include "shell.h"

/**
 * command_parse - function that ...
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

	replace_vars(ctx);
	cmd->name = _strdup(cmd->argv[0], 0, -1);
	return (1);
}

/**
 * find_path - Finds the full path of a command.
 * @ctx: The shell context.
 * Return: The full path of the command, or NULL if not found.
 */
char *find_path(context_t *ctx)
{
	int i = 0, curr_pos = 0;
	char *cmd = ctx->cmd->name;
	char *path = NULL;
	char *pathstr = NULL;

	pathstr = envget(ctx, "PATH=");

	if ((ctx->isatty || pathstr || cmd[0] == '/') && iscmd(cmd))
		return (_strdup(cmd, 0, -1));

	if (!pathstr)
		return (NULL);

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _strdup(pathstr, curr_pos, i - 1);
			if (!*path)
				path = _strcat(&path, cmd);
			else
			{
				path = _strcat(&path, "/");
				path = _strcat(&path, cmd);
			}
			if (iscmd(path))
				return (path);
			if (!pathstr[i])
			{
				free(path);
				break;
			}
			curr_pos = i + 1;
			free(path);
		}
		i++;
	}
	return (NULL);
}

/**
 * iscmd - Checks if a path corresponds to a regular file.
 * @path: The path to check.
 * Return: 1 if the path is a regular file, 0 otherwise.
 */
int iscmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * command_free - Frees memory allocated for the command attributes.
 * @ctx: The shell context containing the command.
 * Return:nothings
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

	if (cmd->path != NULL)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	cmd->argc = 0;
}

/**
 * arg_free - function that free argv
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
