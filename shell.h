#ifndef LITESHELL_H
#define LITESHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * struct alias_node - alias node structure
 * @name: alias name
 * @value: command
 * @next: pointer to the next node
*/
typedef struct alias_node
{
	char *name;
	char *value;
	struct alias_node *next;
} alias_node;

/**
 * struct alias_t - alias list structure
 * @head: pointer to the first node
 * @tail: pointer to the last node
 * @size: list size
*/
typedef struct alias_t
{
	alias_node *head;
	alias_node *tail;
	size_t size;
} alias_t;
alias_t *initAliasList();
int addAlias(alias_t *aliasList, const char *name, const char *value);
alias_node *findAlias(alias_t *aliasList, const char *name);
int removeAlias(alias_t *aliasList, const char *name);
void freeAlias(alias_node *node);
void freeAliasList(alias_t *aliasList);
void freeTokens(char **tokens);
char **tokenize(const char *input_str, const char *delim);
char **tokenizeAliasArguments(char *argument);
int printAliasList(alias_t *aliasList);
int printAlias(alias_node *, const char *);
int handleAlias(alias_t *aliasList, char **arguments);
int handleAliasCommands(alias_t *aliasList, char *argument);
char **tokenizer(char *line, const char *delim);
int executeCommands(char **tokens, char **argv, size_t cmd_count);
extern char **environ;
void get_path(char **pathname);
void handle_env(void);
void handle_setenv(char **tokens);
void handle_unsetenv(char **tokens);
int executeOriginalShell(char **tokens, char **argv);
alias_node *findLastAlias(alias_t *aliasList, const char *name);

#endif
