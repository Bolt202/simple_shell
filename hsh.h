#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 1024

extern char **environ;

int _putchar(char c);
void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void free_memory(char *line, char **args);

#endif /* HSH_H */

