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
		exitcode = _atoi(ctx->cmd->argv[1]);
		if (exitcode == -1)
		{
			_putserror(ctx, "Illegal number: ");
			_eputs(ctx->cmd->argv[1]);
			_eputs("\n");
			ctx->status = 2;
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
		_puts(h->data ? h->data : "(nil)");
		_puts("\n");
		h = h->next;
	}

	return (0);
}

/**
 * envsetfn - function...
 * @ctx:The shell context
 * Return: ...
 */

int envsetfn(context_t *ctx)
{
	command_t *cmd = ctx->cmd;

	if (cmd->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (envset(ctx, cmd->argv[1], cmd->argv[2]))
		return (1);
	return (0);
}

/**
 * envunsetfn - function that ...
 * @ctx:The shell context
 * Return: ...
 */
int envunsetfn(context_t *ctx)
{
	int i;

	if (ctx->cmd->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= ctx->cmd->argc; i++)
		envunset(ctx, ctx->cmd->argv[i]);

	return (0);
}

/**
 * cdfn - changes the current directory of the process
 * @ctx: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int cdfn(context_t *ctx)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;
	char **argv = ctx->cmd->argv;

	s = getcwd(buffer, 1024);
	if (!s)
		_eputs("getcwd failed\n");
	if (!argv[1])
	{
		dir = envget(ctx, "HOME=");
		if (!dir)
		{
			dir = envget(ctx, "PWD=");
			chdir_ret = chdir(dir ? dir : "/");
		}
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		dir = envget(ctx, "OLDPWD=");
		if (!dir)
		{
			_puts(s);
			_puts("\n");
			return (1);
		}
		_puts(dir);
		_puts("\n");
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(argv[1]);
	if (chdir_ret == -1)
	{
		_eputs(ctx->pname);
		_eputs(": ");
		_eputs(ctx->cmd->name);
		_eputs(": ");
		_eputs(argv[1]);
		_eputs(": No such file or directory\n");
	}
	else
	{
		envset(ctx, "OLDPWD", envget(ctx, "PWD="));
		envset(ctx, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
