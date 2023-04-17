#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

/**
 * main - void
 *
 * Return: returns 0
 */

int main(void)
{
	char cmd[MAX_CMD_LEN];
	char *args[] = {cmd, NULL};
	int status;

	while (1)
	{
		printf("$ ");
		if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
		{
			printf("\n");
			exit(0);
		}
		cmd[strlen(cmd) - 1] = '\0';

		if (fork() == 0)
		{
			execve(cmd, args, NULL);
			perror(cmd);
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}

