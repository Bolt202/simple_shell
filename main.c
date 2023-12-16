#include "shell.h"

/**
 * entryPoint - main function
 * @argumentCount: argument count
 * @argumentVector: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int entryPoint(int argumentCount, char **argumentVector)
{
	info_t information[] = { INFO_INIT };
	int fileDescriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDescriptor)
		: "r" (fileDescriptor));

	if (argumentCount == 2)
	{
		fileDescriptor = open(argumentVector[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argumentVector[0]);
				_eputs(": 0: Can't open ");
				_eputs(argumentVector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = fileDescriptor;
	}
	populateEnvironmentList(information);
	readShellHistory(information);
	launchShell(information, argumentVector);
	return (EXIT_SUCCESS);
}

