#include "shell.h"

/**
 * addAlias - add alias to list
 * @aliasList: alias list
 * @name: alias name
 * @value: command
 *
 * Return: 0
*/
int addAlias(alias_t *aliasList, const char *name, const char *value)
{
	alias_node *newAlias = (alias_node *)malloc(sizeof(alias_node));

	if (newAlias == NULL)
	{
		dprintf(2, "Failed to malloc\n");
		return (1);
	}
	newAlias->name = strdup(name);
	newAlias->value = strdup(value);
	newAlias->next = NULL;

	if (aliasList->head == NULL)
		aliasList->head = newAlias;
	else
		aliasList->tail->next = newAlias;

	aliasList->tail = newAlias;
	aliasList->size++;
	return (0);
}

/**
 * findAlias - search alias from list
 * @aliasList: alias list
 * @name: alias name
 *
 * Return: pointer to alias
*/
alias_node *findAlias(alias_t *aliasList, const char *name)
{
	alias_node *currAlias = aliasList->head;

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
			return (currAlias);
		currAlias = currAlias->next;
	}
	return (NULL);
}

/**
 * findLastAlias - get the last alias
 * @aliasList: alias list
 * @name: alias name
 *
 * Return: pointer to last alias
*/
alias_node *findLastAlias(alias_t *aliasList, const char *name)
{
	alias_node *currAlias = aliasList->head;
	alias_node *lastAlias = NULL;

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
			lastAlias = currAlias;
		currAlias = currAlias->next;
	}
	return (lastAlias);
}


/**
 * printAlias -  expand alias
 * @alias: alias to expand
 * @name: alias name
 *
 * Return: 0
*/
int printAlias(alias_node *alias, const char *name)
{
	if (!alias)
	{
		printf("alias: %s not found\n", name);
		return (1);
	}
	printf("%s='%s'\n", alias->name, alias->value);
	return (0);
}

/**
 * removeAlias - remove alias from list
 * @aliasList: alias list
 * @name: alias name
 *
 * Return: 0
*/
int removeAlias(alias_t *aliasList, const char *name)
{
	alias_node *currAlias = aliasList->head, *prevAlias = NULL;

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
		{
			if (prevAlias == NULL)
				aliasList->head = currAlias->next;
			else
				prevAlias->next = currAlias->next;
			freeAlias(currAlias);
			aliasList->size--;
			return (0);
		}
		prevAlias = currAlias;
		currAlias = currAlias->next;
	}
	return (0);
}
