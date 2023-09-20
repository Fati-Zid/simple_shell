#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Externs */
extern char **environ;

/**
 * struct list - Linked list node structure.
 * @data: Data stored in the node.
 * @next: Pointer to the next node.
 */
typedef struct list
{
	char *data;
	struct list *next;
} list_t;

/**
 * struct command - Command structure.
 * @buff: Buffer to store the command.
 * @name: Name of the command.
 * @argv: Array of command arguments. table string
 * @argc: Number of arguments.
 */
typedef struct command
{
	char *buff;
	char *name;
	char **argv;
	int argc;
} command_t;

/**
 * struct context - Shell context structure.
 * @isatty: Flag for interactive mode.
 * @cmd: Pointer to a command structure.
 * @env: Pointer to the environment linked list.
 * @status: Shell exit status.
 */
typedef struct context
{
	int isatty;
	command_t *cmd;
	list_t *env;
	int status;
} context_t;

/**
 * struct builtinfun - Built-in command structure.
 * @type: Name of the built-in command.
 * @func: Pointer to the built-in command function.
 */
typedef struct builtinfun
{
	char *type;
	int (*func)(context_t *);
} builtinfun_t;

/* shell.c */
void hsh(context_t *ctx);

/* context.c */
context_t *context_init(void);
void command_free(context_t *ctx);
void arg_free(char **argv);
void context_free(context_t *ctx);

/* env.c */
size_t envset(context_t *ctx);

/* memory.c */
char *_memset(char *src, char c, size_t n);
void _memcpy(char *dest, const char *src, size_t n);

/* list.c */
list_t *list_push(list_t **head, const char *data);
int list_remove_at(list_t **head, unsigned int index);
void list_free(list_t **head_ptr);

/* string.c */
size_t _strlen(const char *str);
char *_strdup(const char *src);

/* builtin.c */
int envfn(context_t *ctx);

/* io.c */
void _puts(const char *str);
void _putsln(const char *str);

#endif