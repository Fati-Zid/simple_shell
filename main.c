#include "shell.h"

/**
 * main - Entry point of the shell program.
 *
 * This function initializes the shell context, populates the environment,
 * runs the shell loop, and then frees the allocated memory before exiting.
 *
 * Return: ctx->status.
 */
int main(int argc, char **argv)
{
	int exit_status;
	context_t *ctx = context_init(argv[0]);

	if (ctx == NULL)
	{
		exit_status = EXIT_FAILURE;
	}

	envset(ctx);
	hsh(ctx);
	exit_status = ctx->status;
	context_free(ctx);
	return (exit_status);
}
