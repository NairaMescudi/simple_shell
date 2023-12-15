#include "shell.h"

/**
 * tokenizeAliasArguments - make alias tokens
 * @argument: alias name-value pair
 *
 * Return: array of alias name and value
*/
char **tokenizeAliasArguments(char *argument)
{
	char **tokens = NULL, *equalToSign = NULL;
	size_t len_name, len_value;

	tokens = (char **)malloc(sizeof(char *) * 2);
	if (!tokens)
	{
		dprintf(2, "Failed to allocate memory for tokens\n");
		exit(EXIT_FAILURE);
	}
	tokens[0] = NULL;
	tokens[1] = NULL;
	equalToSign = strchr(argument, '=');
	if (equalToSign)
	{
		len_name = equalToSign - argument;
		tokens[0] = (char *)malloc(len_name + 1);
		if (!tokens[0])
			exit(EXIT_FAILURE);
		strncpy(tokens[0], argument, len_name);
		tokens[0][len_name] = '\0';
		len_value = strlen(equalToSign + 1);
		tokens[1] = (char *)malloc(len_value + 1);
		if (!tokens[1])
		{
			free(tokens[0]);
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[1], equalToSign + 1, len_value);
		tokens[1][len_value] = '\0';
	}
	else
		tokens[0] = strdup(argument);
	if (!tokens[0] && !tokens[1])
	{
		free(tokens);
		return (NULL);
	}
	return (tokens);
}

/**
 * handleAlias - handle aliases
 * @aliasList: alias list
 * @arguments: command arguments
 *
 * Return: 0
*/
int handleAlias(alias_t *aliasList, char **arguments)
{
	int i;

	if (!arguments[0])
		printAliasList(aliasList);
	for (i = 0; arguments[i]; ++i)
		handleAliasCommands(aliasList, arguments[i]);
	return (0);
}

/**
 * handleAliasCommands - handle alias commands
 * @aliasList: alias list
 * @argument: command arguments
 *
 * Return: 0
*/
int handleAliasCommands(alias_t *aliasList, char *argument)
{
	char **aliasTokens = tokenizeAliasArguments(argument);
	char *name = aliasTokens[0], *value = aliasTokens[1];
	char *chainedValue = NULL;
	alias_node *alias = NULL, *lastAlias = NULL;

	if (value == NULL)
	{
		lastAlias = findLastAlias(aliasList, name);
		printAlias(lastAlias, name);
	}
	else
	{
		alias = findAlias(aliasList, name);
		if (alias == NULL)
			addAlias(aliasList, name, value);
		else
		{
			chainedValue = malloc(strlen(name)
					+ strlen("=")
					+ strlen(value)
					+ 1);
			sprintf(chainedValue, "%s=%s", name, value);
			free(alias->value);
			alias->value = chainedValue;
		}
	}
	freeTokens(aliasTokens);
	aliasTokens = NULL;
	return (0);
}

/**
 * initAliasList - make alias list
 * @aliasList: alias list
 *
 * Return: a pointer to alias list
*/
alias_t *initAliasList(alias_t *aliasList)
{
	if (aliasList != NULL)
		return (aliasList);

	aliasList = (alias_t *)malloc(sizeof(alias_t));
	if (aliasList == NULL)
		return (NULL);

	aliasList->head = NULL;
	aliasList->tail = NULL;
	aliasList->size = 0;
	return (aliasList);
}
