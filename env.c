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

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) &&
		(_starts_with(cmd, "./") ||
		_starts_with(cmd, "/") ||
		_starts_with(cmd, "../"))
	)
	{
		if (iscmd(cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _strdup(pathstr, curr_pos, i - 1);
			if (!*path) {
				printf("first\n");
				_strcat(&path, cmd);
			}
			else
			{
				printf("second\n");
				_strcat(&path, "/");
				_strcat(&path, cmd);
			}
			if (iscmd(path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i + 1;
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
 * envget - Gets the value of an environment variable.
 * @ctx: The shell context.
 * @name: The name of the environment variable.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *envget(context_t *ctx, const char *name)
{
	list_t *node = ctx->env;
	char *p;

	while (node)
	{
		p = _starts_with(node->data, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}