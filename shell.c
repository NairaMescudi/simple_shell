#include "shell.h"


char **tokenizer(char *line, const char *delim)
{
	char *dup_line = NULL, *token = NULL, **tokens = NULL;
	size_t i, tok_count = 0;

	/* check if line is NULL */
	if (!line || !(*line))
		return (NULL);

	/* duplicate line for counting tokens */
	dup_line = strdup(line);
	token = strtok(dup_line, delim);
	while (token)
	{
		++tok_count;
		token = strtok(NULL, delim);
	}
	free(dup_line);
	/* allocate enough mem for tokens array */
	if (tok_count > 0)
	{
		tokens = malloc(sizeof(char *) * (tok_count + 1));
		if (tokens == NULL)
		{
			fprintf(stderr, "malloc failed\n");
			exit(EXIT_FAILURE);
		}
		tokens[tok_count] = NULL;
		/* store tokens in alloced array */
		token = strtok(line, delim);
		for (i = 0; token; i++)
		{
			tokens[i] = strdup(token);
			token = strtok(NULL, delim);
		}
	}
	tok_count = 0;
	return (tokens);
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

/**
  * 1. Get commands and tokenize 
  * 2. Fork a new process based on command
  * 3. Wait the parent process
  * 4. Pass the tokenized input into the execve call
  * 5. Execute the commands
  * 6. Repeat
  */
int main(__attribute__((unused))int argc, char **argv)
{
	ssize_t bytesR = 0, cmd_count = 0;
	size_t n;
	char *line = NULL, **tokens = NULL;
	int exitCode;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		fflush(stdout);
		++cmd_count;

		bytesR = getline(&line, &n, stdin);
		if (bytesR == -1) /* errors and EOF */
		{
			free(line);
			/**freeTokens(tokens);*/
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(EXIT_FAILURE);
		}
		line[bytesR - 1] = '\0';		
		tokens = tokenizer(line, " ");
		if (!tokens)
			continue;
		exitCode = executeCommand(tokens, argv, cmd_count);
		if (exitCode != 0)
		{
			printf("Command exited with status %d\n", exitCode);
		}
		freeTokens(tokens);
	}
	free(line);
	line = NULL;
	return (0);
}

int executeCommand(char **tokens, char **argv, size_t cmd_count)
{
	pid_t pid;
	int status;

	if (!tokens || !tokens[0])
		return (0);

	if (access(tokens[0], X_OK) == -1)
	{
		fprintf(stderr, "%s: %ld: %s not found\n", argv[0], cmd_count,
				tokens[0]);
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		if (execve(tokens[0], tokens, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);

	return (WIFEXITED(status) ? WEXITSTATUS(status) : 0);
}
