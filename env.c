#include "shell.h"

void exec_env(void)
void handle_env(void)
{
	char *command[] = {"sh", "-c", "env", NULL};
	char **env = environ;
	pid_t pid = fork();

	if (pid == 0)
	{
		/* This is the child process */
		execve("/bin/sh", command, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* This is the parent process */
		/* Wait for the child to complete */
		waitpid(pid, NULL, 0);
}

void handle_setenv(char **tokens)
{
	if (!tokens[1] || !tokens[2] || tokens[3])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}
	if (setenv(tokens[1], tokens[2], 1))
		perror("setenv");
}

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
