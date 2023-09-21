#include "shell.h"

/**
 * read_input - Reads input from stdin into the command buffer of the context.
 * @ctx: The shell context.
 * Return: The number of characters read (excluding newline), or -1 on failure.
 */
ssize_t read_input(context_t *ctx)
{
	ssize_t r = 0;
	size_t buff_size = 0;
	char *buff = NULL;

	r = getline(&buff, &buff_size, stdin);

	if (r > 0)
	{
		if (buff[r - 1] == '\n')
		{
			buff[r - 1] = '\0';
			r--;
		}

		if (is_white_space(buff))
			r = 0;
	}

	ctx->cmd->buff = buff;
	
	return (r);
}
