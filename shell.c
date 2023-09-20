#include "shell.h"

/**
 * hsh - Executes the main shell loop.
 * @ctx: The shell context.
 */
void hsh(context_t *ctx)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -3 && ctx->status == 0)
	{
		if (ctx->isatty)
			_puts("($) ");

		r = read_input(ctx);

		if (r > 0)
		{
			command_parse(ctx);

			printf("BUFF: %s | NAME: %s | ARG: %d\n"; ctx->cmd->buff, ctx->cmd->name, ctx->cmd->argc);
			for(int i=0; i<ctx->cmd->argc; i++) {
				printf("\t%s\n", ctx->cmd->argv[i]);
			}

			ret = exec_builtin(ctx);
			if (ret == -1)
				exec_cmd(ctx);
		}
		else if (r == -1 && ctx->isatty)
		{
			_puts("\n");
		}
		command_free(ctx);
	}
}

/**
 * exec_builtin - Executes a built-in command if available.
 * @ctx: The shell context.
 * Return: The return value of the built-in command, -1 if not found.
 */
int exec_builtin(context_t *ctx)
{
	int i, ret = -1;
	builtinfun_t table[] = {
		{"exit", exitfn},
		{"env", envfn},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
	{
		if (_strcmp(ctx->cmd->name, table[i].type) == 0)
		{
			ret = table[i].func(ctx);
			break;
		}
	}
	return (ret);
}

/**
 * exec_cmd - Executes a command.
 * @ctx: The shell context.
 * Return: 0 on success, -1 on failure.
 */
void exec_cmd(context_t *ctx)
{
	pid_t child_pid;
	static char *newenviron[] = {NULL};
	command_t *cmd = ctx->cmd;
	int status = 0;

	cmd->path = find_path(ctx);

	if (cmd->path)
	{
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			return;
		}

		if (child_pid == 0)
		{
			if(execve(cmd->path, cmd->argv, newenviron) == -1)
			{
				command_free(ctx);
				context_free(ctx);
				if (errno == EACCES)
					exit(126);
				exit(1);
			}
		}
		else
		{
			wait(&(status));
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				if (status == 126)
					_putserror(ctx, "Permission denied");
			}
		}
	}
	else
		_putserror(ctx, "command not found");
}

