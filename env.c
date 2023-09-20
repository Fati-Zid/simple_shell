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

int envset(context_t *ctx, char *var, char *value)
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
			ctx->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	list_push(&(ctx->env), buf);
	free(buf);
	ctx->env_changed = 1;
	return (0);
}

void envunset(context_t *ctx, char *var)
{
	list_t *node = ctx->env;
	unsigned int i = 0;
	char *p;

	if (!node || !var)
		return;

	while (node)
	{
		p = _starts_with(node->data, var);
		if (p && *p == '=')
		{
			ctx->env_changed = list_remove_at(&(ctx->env), i);
			i = 0;
			node = ctx->env;
			continue;
		}
		node = node->next;
		i++;
	}
}

char **get_environ(context_t *ctx)
{
	if (!ctx->environ || ctx->env_changed)
	{
		ctx->environ = list_to_strings(ctx->env);
		ctx->env_changed = 0;
	}

	return (ctx->environ);
}