#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int printf(const char *format, ...);
int scanf(const char *format, ...);
char *fgets(char *s, int size, FILE *stream);
int puts(const char *s);

void *malloc(size_t size);
void free(void *ptr);
void exit(int status);
int system(const char *command);

int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
char *strtok(char *str, const char *delim);

pid_t fork(void);
int execvp(const char *file, char *const argv[]);
int pipe(int pipefd[2]);
int chdir(const char *path);

pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);

#endif
