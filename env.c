#include "shell.h"

/**
 * handle_env - print env variables
 *
 * Return: nothing
*/
void handle_env(void)
{
	char *command[] = {"sh", "-c", "env", NULL};
	char **env = environ;
	pid_t pid = fork();

	if (pid == 0)
	{
		execve("/bin/sh", command, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

/**
 * handle_setenv - set env variables
 * @tokens: array of string
 *
 * Return: nothing
*/
void handle_setenv(char **tokens)
{
	char *currentEnv = NULL;

	if (!tokens[1] || !tokens[2] || tokens[3])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}
	currentEnv = getenv(tokens[1]);
	if (currentEnv == NULL)
	{
		if (setenv(tokens[1], tokens[2], 1))
			perror("setenv");
	}
	else
	{
		unsetenv(tokens[1]);
		setenv(tokens[1], tokens[2], 1);
	}
}

/**
 * handle_unsetenv - set env variables
 * @tokens: array of string
 *
 * Return: nothing
*/
void handle_unsetenv(char **tokens)
{
	if (!tokens[1] || tokens[2])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}
	if (unsetenv(tokens[1]))
		perror("unsetenv");
}
