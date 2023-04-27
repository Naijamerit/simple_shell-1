#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_LINE 80

/**
 * search_path - it searches a command in PATH
 * @cmd: a command to search for
 *
 * Return: the full path of the command if found, otherwise NULL
 */
char *search_path(char *cmd)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");
char *full_path = malloc(MAX_LINE);

while (dir != NULL)
{
sprintf(full_path, "%s/%s", dir, cmd);
	if (access(full_path, X_OK) == 0)
	{
	free(path_copy);
	return (full_path);
	}
	dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);
	return (NULL);
}

/**
 * main - runs a simple shell
 *
 * Return: 0 if successful
 */
int main(void)
{
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;
	int status;
	char line[MAX_LINE];
	pid_t pid;

	while (should_run)
	{
	write(STDOUT_FILENO, "coh> ", 5);
	fflush(stdout);
	fgets(line, MAX_LINE, stdin);
	line[strcspn(line, "\n")] = '\0';

	int i = 0;

	args[i] = strtok(line, " ");

	while (args[i] != NULL)
	{
	i++;
	args[i] = strtok(NULL, " ");
	}

	char *cmd_path = search_path(args[0]);

	if (cmd_path != NULL)
	{
	pid = fork();
	if (pid == 0)
	{
	execv(cmd_path, args);
	}
	else
	{
	wait(&status);
	}
	free(cmd_path);
	}
	else
	{
	write(STDERR_FILENO, args[0], strlen(args[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	}
	return (0);
	}
}
