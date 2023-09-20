#include "shell.h"

/**
 * hsh - Executes the main shell loop.
 * @ctx: The shell context.
 */
void hsh(context_t *ctx)
{
    printf("STATUS: %d", ctx->status);

    envfn(ctx);
}