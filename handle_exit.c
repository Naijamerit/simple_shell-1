#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * This program is a simple shell that allows the user to enter commands,
 * executes them, and displays the output.
 */
char *find_executable(char *command)
{
	char *path = getenv("PATH");
	char *path_token = strtok(path, ":");

	while (path_token != NULL)
	{
	char *executable = (char *)malloc(strlen(path_token) + strlen(command) + 2);

	sprintf(executable, "%s/%s", path_token, command);

	if (access(executable, X_OK) == 0)
	{
		return (executable);
	}

	free(executable);
	path_token = strtok(NULL, ":");
	}

	return (NULL);
}

int execute_command(char *command, char **arguments)
	{

	if (strcmp(arguments[0], "exit") == 0)
	{
	return (0);
	}
	char *executable = find_executable(arguments[0]);

	if (executable == NULL)
	{
	fprintf(stderr, "Command not found: %s\n", arguments[0]);
		return (1);
	}

	pid_t pid = fork();
	if (pid < 0)
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	if (execve(executable, arguments, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	}
	else
	{
	int status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
	fprintf(stderr, "Command '%s' failed with exit status %d\n",
			command, WEXITSTATUS(status));
		}
	}

	free(executable);

	return (1);
}

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];

	while (1)
	{
	printf("$ ");

		if (fgets(command, sizeof(command), stdin) == NULL)
	{
		printf("\n");
		break;
	}

	command[strcspn(command, "\n")] = '\0';
	int argc = 0;
	char *token = strtok(command, " ");
		while (token != NULL && argc < MAX_ARGUMENTS - 1)
		{
		arguments[argc++] = token;
		token = strtok(NULL, " ");
	}
	arguments[argc] = NULL;

		int should_continue = execute_command(command, arguments);
		
		if (!should_continue)
		{
		break;
		}
	}

	return (0);
}
