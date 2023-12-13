#include "shell.h"
void exec_env() {
	char *command[] = {"sh", "-c", "env", NULL};
	char **env = environ;

	/* Create a child process */
	pid_t pid = fork();

	if (pid == 0) {
		/* This is the child process */
		execve("/bin/sh", command, env);
		/* execve only returns if an error occurs */
		perror("execve");
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		/* Fork failed */
		perror("fork");
		exit(EXIT_FAILURE);
	} else {
		/* This is the parent process */
		/* Wait for the child to complete */
		waitpid(pid, NULL, 0);
	}
}

void handle_setenv(char **tokens)
{
    if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] != NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }

    if (setenv(tokens[1], tokens[2], 1) != 0)
    {
        perror("setenv");
    }
}

void handle_unsetenv(char **tokens)
{
    if (tokens[1] == NULL || tokens[2] != NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    if (unsetenv(tokens[1]) != 0)
    {
        perror("unsetenv");
    }
}
