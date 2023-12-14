#include "shell.h"

int main(__attribute__((unused))int argc, char **argv);

/**
 * tokenizer - make tokens from string
 * @line: string to tokenise
 * @delim: string delimiter
 *
 * Return: an array of tokens
 */
char **tokenizer(char *line, const char *delim)
{

	char *token = NULL;
	int i = 0;
	char **tokens = malloc(sizeof(char *) * 100);

	while (i < 100)
  {
    if (!line || !(*line))
		return (NULL);
  }
	dup_line = strdup(line);
	token = strtok(dup_line, delim);
	while (token)
	{
		tokens[i] = NULL;
		i++;
	}
	i = 0;
	token = strtok(line, delim);
	while (token)
	{
		tokens[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(tokens[i], token);
		token = strtok(NULL, delim);
		i++;
	free(dup_line);
	if (tok_count > 0)
	{
		tokens = malloc(sizeof(char *) * (tok_count + 1));
		if (tokens == NULL)
		{
			fprintf(stderr, "malloc failed\n");
			exit(EXIT_FAILURE);
		}
		tokens[tok_count] = NULL;
		token = strtok(line, delim);
		for (i = 0; token; i++)
		{
			tokens[i] = strdup(token);
			token = strtok(NULL, delim);
		}
	}
	if (tokens[0] == NULL)
		return (NULL);
	else
		return (tokens);
	return (NULL);
}

/**
 * read_command - read user input
 * @list: list of aliases
 * @status: command return value
 *
 * Description: read users input from stdout
 * using getline()
 *
 * Return: user input (string)
 */
char *read_command(alias_t *list, int status)
{
	char *line = NULL;
	size_t n;
	ssize_t bytesR = 0;

	bytesR = getline(&line, &n, stdin);

	if (bytesR == -1) /* errors and EOF */
	{
		free(line);
		freeAliasList(list);

		exit(status);
	}

	return (line);
/**	if (!tokens)
*		return;
*	for (i = 0; tokens[i]; i++)
*	{
*		free(tokens[i]);
*		tokens[i] = NULL;
*	}
*	free(tokens);
*	tokens = NULL;
*/}

/**
 * main - run a shell instance
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: dependent on syscalls status
 */
int main(__attribute__((unused))int argc, char **argv)
{
	ssize_t cmd_count = 0;
	char *line = NULL, **tokens = NULL;
	int lastExitCode = 0;
	alias_t *aliasList = initAliasList(NULL);
	alias_node *alias = NULL;

	while (1)
	{
		print_prompt();
		++cmd_count;
		line = read_command(aliasList, lastExitCode);
		tokens = tokenizer(line, " \n\t\r");


/**		bytesR = getline(&line, &n, stdin);
*		if (bytesR == -1) 
*		{
*			free(line);
*			if (isatty(STDIN_FILENO))
*				printf("\n");
*			freeAliasList(aliasList);
*			exit(lastExitCode);
*		}
*		line[bytesR - 1] = '\0';
*/		tokens = tokenizer(line, " ");
		if (!tokens)
		{
			_free(line);
			continue;
		}
		if (strcmp(tokens[0], "alias") == 0)
			handleAlias(aliasList, tokens + 1);
		else if (strcmp(tokens[0], "setenv") == 0)
			handle_setenv(tokens);
		else if (strcmp(tokens[0], "unsetenv") == 0)
			handle_unsetenv(tokens);
		else
		{
			if (strcmp(tokens[0], "alias") == 0)
				handleAlias(aliasList, tokens + 1);
			else
			{
				alias = findAlias(aliasList, tokens[0]);

				if (alias)
				{
					free(tokens[0]);
					tokens[0] = strdup(alias->value);
				}
				if (strcmp(tokens[0], "exit") == 0)
					handle_exit(tokens, line, aliasList, lastExitCode);
				if (strcmp(tokens[0], "env") == 0 || strcmp(tokens[0], "printenv") == 0)
				{
					_free(line);
					exec_env();
					freeTokens(tokens);
					continue;
				}
				lastExitCode = executeCommand(tokens, argv, cmd_count);
				_free(line);
				handle_env();
				freeTokens(tokens);
				continue;
			}
		}
		_free(line);
		freeTokens(tokens);
	}
	_free(line);
	return (0);
}

/**
 * executeCommand - execute command
 * @tokens: an array of tokens
 * @argv: argument vector
 * @cmd_count: command count for each session
 *
 * Return: command status
 */
int executeCommand(char **tokens, char **argv, size_t cmd_count)
{
	pid_t pid;
	int status, exitCode;

	if (!tokens || !tokens[0])
		return (0);

	if (access(tokens[0], X_OK) == -1)
	{
		get_path(&tokens[0]);
		if (tokens && access(tokens[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: %ld: %s: not found\n",
					argv[0], cmd_count, tokens[0]);
			return (127);
		}
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
			exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
	exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : 0;
	return (exitCode);
}

/**
 * get_path - get command path
 * @pathname: command to execute
 *
 * Return: nothing
 */
void get_path(char **pathname)
{
	char *token = NULL, *path = NULL, *fullpath = NULL, *dup_path;

	if (!pathname || !(*pathname))
		return;

	path = getenv("PATH");
	if (path == NULL)
		return;

	dup_path = strdup(path);
	token = strtok(dup_path, ":");
	while (token)
	{
		fullpath = malloc(sizeof(char) * (strlen(token) +
					strlen(*pathname) + 2));
		fullpath = malloc(sizeof(char) * (strlen(token)
					+ strlen(*pathname) + 2));
		sprintf(fullpath, "%s/%s", token, *pathname);

		if (access(fullpath, X_OK) == 0)
		{
			free(*pathname);
			*pathname = strdup(fullpath);
			free(fullpath);
			break;
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}
	free(dup_path);
	dup_path = NULL;
}
