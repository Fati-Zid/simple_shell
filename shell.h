#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>

/* Externs */
extern char **environ;

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

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
 * @path: the path
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
 * @pname: Process name
 * @error_count: Number of occured erros
 * @environ: String of environement variables
 * @env_changed: 1 if environement is changed, 0 otherwise
*/
typedef struct context
{
	char *pname;
	int isatty;
	command_t *cmd;
	int status;
	int error_count;
	char **environ;
	list_t *env;
	int env_changed;
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
void fork_cmd(context_t *ctx);

/* context.c */
context_t *context_init(char *pname);
void context_free(context_t *ctx);

/* env.c */
size_t env_populate(context_t *ctx);
char *envget(context_t *ctx, const char *name);
int envset(context_t *ctx, char *var, char *value);
void envunset(context_t *ctx, char *var);
char **get_environ(context_t *ctx);

/* memory.c */
char *_memset(char *src, char c, size_t n);
void _memcpy(char *dest, const char *src, size_t n);

/* list.c */
list_t *list_push(list_t **head, const char *data);
unsigned int list_remove_at(list_t **head, unsigned int index);
char **list_to_strings(list_t *head);
size_t list_len(const list_t *h);
void list_free(list_t **head_ptr);

/* list_ext.c */
list_t *node_starts_with(list_t *node, char *prefix, char c);

/* string.c */
size_t _strlen(const char *str);
char *_strdup(const char *str, int start, int stop);
unsigned int _strcmp(const char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char **str1, char *str2);

/* string_ext.c */
char *_starts_with(const char *haystack, const char *needle);
int is_white_space(char *str);
char *_strchr(char *s, char c);

/* builtin.c */
int exitfn(context_t *ctx);
int envfn(context_t *ctx);
int envsetfn(context_t *ctx);
int envunsetfn(context_t *ctx);
int cdfn(context_t *ctx);

/* output.c */
void _puts(const char *str);
void _putsln(const char *str);
void _eputs(const char *str);
void _putserror(context_t *ctx, const char *error);

/* input.c */
ssize_t read_input(context_t *ctx);

/* command.c */
unsigned int command_parse(context_t *ctx);
char *find_path(context_t *ctx);
int iscmd(char *path);
void command_free(context_t *ctx);
void arg_free(char **argv);

/* tokenizer.c */
char **strtow(char *str, int *len, char *d);
int is_delim(char c, char *delim);

/* utils.c */
int _atoi(char *s);
char *_itoa(long int num, int base, int flags);

/* vars.c */
int replace_vars(context_t *ctx);
int replace_string(char **old, char *new);

#endif
