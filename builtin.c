#include "shell.h"

/**
 * builtin_exit - Exits the shell with a specified exit status.
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status.
 *         (0) if info.argv[0] != "exit".
 */
int builtin_exit(info_t *info)
{
	int exitValue;

	if (info->argv[1])  /* Check if there is an exit argument */
	{
		exitValue = _erratoi(info->argv[1]);

		if (exitValue == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exitValue;
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * builtin_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int builtin_cd(info_t *info)
{
	char *currentPath, *targetDir, buffer[1024];
	int chdirResult;

	currentPath = getcwd(buffer, 1024);
	if (!currentPath)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
		handle_cd_no_args(info, &targetDir, &chdirResult);
	else if (_strcmp(info->argv[1], "-") == 0)
		handle_cd_dash(info, currentPath, &targetDir, &chdirResult);
	else
		handle_cd_with_args(info, &chdirResult);

	return (0);
}

/**
 * builtin_help - Provides assistance. (Function not yet implemented)
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int builtin_help(info_t *info)
{
	char **argumentArray;

	argumentArray = info->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*argumentArray); /* Temporary unused argument workaround */

	return (0);
}

