#include "shell.h"

/**
 * isExecutableCommand - checks if a file is an executable command
 * @information: the information struct
 * @filePath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCommand(info_t *information, char *filePath)
{
	struct stat fileStats;

	(void)information;

	if (!filePath || stat(filePath, &fileStats))
		return 0;

	if (S_ISREG(fileStats.st_mode))
		return 1;

	return 0;
}

/**
 * duplicateCharacters - creates a duplicate of characters within a range
 * @pathString: the PATH string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to the new buffer
 */
char *duplicateCharacters(char *pathString, int start, int end)
{
	static char buffer[1024];
	int bufferIndex = 0, pathIndex;

	for (pathIndex = start; pathIndex < end; pathIndex++)
	{
		if (pathString[pathIndex] != ':')
			buffer[bufferIndex++] = pathString[pathIndex];
	}

	buffer[bufferIndex] = '\0';
	return buffer;
}

/**
 * findCommandPath - locates the command in the PATH string
 * @information: the information struct
 * @pathString: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *findCommandPath(info_t *information, char *pathString, char *command)
{
	int pathIndex = 0, currentPosition = 0;
	char *path;

	if (!pathString)
		return NULL;

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (isExecutableCommand(information, command))
			return command;
	}

	while (1)
	{
		if (!pathString[pathIndex] || pathString[pathIndex] == ':')
		{
			path = duplicateCharacters(pathString, currentPosition, pathIndex);

			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}

			if (isExecutableCommand(information, path))
				return path;

			if (!pathString[pathIndex])
				break;

			currentPosition = pathIndex;
		}
		pathIndex++;
	}
	return NULL;
}

