#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>

/* Structs */
/**
 * struct list_node - A node in a linked list.
 * @str: The string data stored in the node.
 * @next: A pointer to the next node in the list.
 */
struct list_node
{
	char *str;
	struct list_node *next;
};

/**
 * struct argument_info - Information about command line arguments.
 * @argv: An array of strings containing the command line arguments.
 * @argc: The number of command line arguments.
 */
struct argument_info
{
	char **argv;
	int argc;
};

/**
 * struct built_in_command - A built-in command supported by the shell.
 * @command: The name of the built-in command.
 * @function: A pointer to the function that implements the command.
 */
struct built_in_command
{
	char *command;
	int (*function)(struct argument_info *);
};

/* Function Prototypes */
int main(int argc, char **argv);

#endif /* SHELL_H */

