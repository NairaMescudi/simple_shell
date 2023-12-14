#include "shell.h"

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

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
			return (currAlias);
		currAlias = currAlias->next;
	}
	return (NULL);
}


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
 * alias_node *findLastAlias(alias_t *aliasList, const char *name)
 * {
 *    alias_node *currAlias = findAlias(aliasList, name);
 *
 *    while (currAlias && currAlias->value
 *		    && currAlias->value[0] == 'a'
 *		    && currAlias->value[1] == 'l'
 *		    && currAlias->value[2] == 'i'
 *		    && currAlias->value[3] == 'a'
 *		    && currAlias->value[4] == 's'
 *		    )
 *    {
 *        currAlias = findAlias(aliasList, currAlias->value + 5);
 *    }
 *
 *    return currAlias;
 * }
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
