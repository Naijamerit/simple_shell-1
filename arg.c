#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_LENGTH 100
/**
 * Takes and argument
 * returns 0
 */

void handleCommand(char* command)
{
	int argc = 0;
	char *argv[MAX_LENGTH/2 + 1];

	char *token = strtok(command, " \n");
	while (token != NULL) 
		{
		argv[argc++] = token;
		token = strtok(NULL, " \n");
		}

	argv[argc] = NULL;

	pid_t pid = fork();
	if (pid == 0) {
	if (execvp(argv[0], argv) == -1) 
		{
		printf("Command not found: %s\n", argv[0]);
		exit(1);
		}
	} 
	else if (pid < 0) 
	{
		printf("Fork failed\n");
	} 
	else 
	{
		wait(NULL);
	}
}

int main() {
	char input[MAX_LENGTH];

	while (1) 
    {
	printf(":) ");
	fflush(stdout);
	fgets(input, MAX_LENGTH, stdin);

	if (strcmp(input, "exit\n") == 0)
		break;

		handleCommand(input);
	}

    return 0;
}
