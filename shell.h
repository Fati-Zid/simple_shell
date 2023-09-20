#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	char *path;
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
	char *pname;
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
int exec_builtin(context_t *ctx);
void exec_cmd(context_t *ctx);

/* context.c */
context_t *context_init(char *pname);
void context_free(context_t *ctx);

/* env.c */
size_t envset(context_t *ctx);
char *find_path(context_t *ctx);
int iscmd(char *path);
char *envget(context_t *ctx, const char *name);

/* memory.c */
char *_memset(char *src, char c, size_t n);
void _memcpy(char *dest, const char *src, size_t n);

/* list.c */
list_t *list_push(list_t **head, const char *data);
unsigned int list_remove_at(list_t **head, unsigned int index);
void list_free(list_t **head_ptr);

/* string.c */
size_t _strlen(const char *str);
char *_strdup(const char *str, int start, int stop);
unsigned int _strcmp(const char *str1, const char *str2);
char *_starts_with(const char *haystack, const char *needle);
char *_strcat(char **str1, char *str2);

/* builtin.c */
int exitfn(context_t *ctx);
int envfn(context_t *ctx);

/* output.c */
void _puts(const char *str);
void _putsln(const char *str);
void _putserror(context_t *ctx, const char *error);

/* input.c */
ssize_t read_input(context_t *ctx);

/* command.c */
unsigned int command_parse(context_t *ctx);
void command_free(context_t *ctx);
void arg_free(char **argv);

/* tokenizer.c */
char **strtow(char *str, int *len, char *d);
int is_delim(char c, char *delim);

#endif