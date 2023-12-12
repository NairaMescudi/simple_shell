#include "shell.h"

int printAliasList(alias_t *aliasList)
{
    alias_node *currAlias = aliasList->head;

    while (currAlias)
    {
        printf("%s='%s'\n", currAlias->name, currAlias->value);
        currAlias = currAlias->next;
    }
    return 0;
}

void freeAlias(alias_node *node)
{
    if (node)
    {
        free(node->name);
        free(node->value);
	free(node);
    }
}

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
