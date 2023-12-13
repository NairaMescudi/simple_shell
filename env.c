#include "shell.h"
/**void printenv(void)
*{
*   pid_t pid;
*    int status;
*
*    pid = fork();
*
*    if (pid == -1)
*    {
*        perror("fork");
*        exit(EXIT_FAILURE);
*    }
*
*    if (pid == 0)
*    {
*        char *const env_cmd[] = {"/usr/bin/env", NULL};
*        if (execve("/usr/bin/env", env_cmd, NULL) == -1)
*        {
*            perror("execve");
*            exit(EXIT_FAILURE);
*        }
*    }
*    else
*    {
*        waitpid(pid, &status, 0);
*    }
*}
*/

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
/**
*{
*        int i = 0;
*
*        while (environ[i] != NULL)
*        {
*                printf("%s\n", environ[i]);
*                ++i;
*        }
*}
*/
