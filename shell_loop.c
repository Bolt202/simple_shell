#include "shell.h"

/**
 * shellMainLoop - main loop for the shell
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shellMainLoop(info_t *info, char **av)
{
	ssize_t inputResult = 0;
	int builtinResult = 0;

	while (inputResult != -1 && builtinResult != -2)
	{
		clearInfo(info);

		if (isInteractive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);
		inputResult = getInput(info);

		if (inputResult != -1)
		{
			setInfo(info, av);
			builtinResult = findBuiltin(info);

			if (builtinResult == -1)
				findCommand(info);
		}
		else if (isInteractive(info))
			_putchar('\n');

		freeInfo(info, 0);
	}

	writeHistory(info);
	freeInfo(info, 1);

	if (!isInteractive(info) && info->status)
		exit(info->status);

	if (builtinResult == -2)
	{
		if (info->errNum == -1)
			exit(info->status);
		exit(info->errNum);
	}

	return builtinResult;
}

/**
 * findBuiltin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *        -2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
	int i, builtinResult = -1;

	builtinTable builtins[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].type; i++)
		if (_strcmp(info->argv[0], builtins[i].type) == 0)
		{
			info->lineCount++;
			builtinResult = builtins[i].func(info);
			break;
		}

	return builtinResult;
}

/**
 * findCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}

	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelimiter(info->arg[i], " \t\n"))
			k++;

	if (!k)
		return;

	path = findPath(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((isInteractive(info) || _getenv(info, "PATH=") ||
			info->argv[0][0] == '/') && isCmd(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * forkCommand - forks a new process to execute a command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(info_t *info)
{
	pid_t childPid;

	childPid = fork();

	if (childPid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (childPid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			freeInfo(info, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}

