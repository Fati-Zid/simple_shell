#include "shell.h"

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
		_putsln(h->data ? h->data : "(nil)");
		h = h->next;
	}

	return (0);
}