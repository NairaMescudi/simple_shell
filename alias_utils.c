#include "shell.h"

/**
 * printAliasList - print alias list
 * @aliasList: alias list
 *
 * Return: 0
*/
int printAliasList(alias_t *aliasList)
{
	alias_node *currAlias = aliasList->head;

	while (currAlias)
	{
		printf("%s='%s'\n", currAlias->name, currAlias->value);
		currAlias = currAlias->next;
	}
	return (0);
}

/**
 * freeAlias - free alias node
 * @node: alias node to free
 *
 * Return: nothing
*/
void freeAlias(alias_node *node)
{
	if (node)
	{
		free(node->name);
		free(node->value);
		free(node);
	}
}

/**
 * freeAliasList - free alias list
 * @aliasList: alias list to free
 *
 * Return: nothing
*/
void freeAliasList(alias_t *aliasList)
{
	alias_node *currAlias = aliasList->head, *nextAlias = NULL;

	while (currAlias)
	{
		nextAlias = currAlias->next;
		freeAlias(currAlias);
		currAlias = nextAlias;
	}
	free(aliasList);
}
