#include "shell.h"

/**
 * envset - Populates the shell environment list.
 * @ctx: The shell context.
 * Return: The number of environment variables.
 */
size_t env_populate(context_t *ctx)
{
	list_t *env = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		list_push(&env, environ[i]);
	ctx->env = env;
	return (i);
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

int envset(context_t *context, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(&buf, "=");
	_strcat(&buf, value);
	node = ctx->env;
	while (node)
	{
		p = _starts_with(node->data, var);
		if (p && *p == '=')
		{
			free(node->data);
			node->data = buf;
			return (0);
		}
		node = node->next;
	}
	list_push(&(ctx->env), buf);
	free(buf);
	return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}