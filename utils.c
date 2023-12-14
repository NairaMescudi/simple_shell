#include "shell.h"

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");
	fflush(stdout);
}

void freeTokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i]; i++)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(tokens);
	tokens = NULL;
}

void _free(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void handle_exit(char **arr, char *ptr, alias_t *list, int status)
{
	freeTokens(arr);
	_free(ptr);
	freeAliasList(list);
	exit(status);
}
