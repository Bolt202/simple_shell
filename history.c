#include "shell.h"

/**
 * obtainHistoryFile - retrieves the history file path
 * @info: parameter structure
 *
 * Return: allocated string containing the history file path
 */
char *obtainHistoryFile(info_t *info)
{
	char *directory, *filePath;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);

	filePath = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!filePath)
		return (NULL);

	filePath[0] = '\0';
	_strcpy(filePath, directory);
	_strcat(filePath, "/");
	_strcat(filePath, HIST_FILE);

	return (filePath);
}

/**
 * recordHistory - creates or appends to a history file
 * @info: the parameter structure
 *
 * Return: 1 on success, -1 on failure
 */
int recordHistory(info_t *info)
{
	ssize_t fileDescriptor;
	char *fileName = obtainHistoryFile(info);
	list_t *currentNode = NULL;

	if (!fileName)
		return (-1);

	fileDescriptor = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);

	if (fileDescriptor == -1)
		return (-1);

	for (currentNode = info->history; currentNode; currentNode = currentNode->next)
	{
		_putsfd(currentNode->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}
	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);

	return (1);
}

/**
 * retrieveHistory - reads history from a file
 * @info: the parameter structure
 *
 * Return: number of history entries on success, 0 on failure
 */
int retrieveHistory(info_t *info)
{
	int i, last = 0, lineCount = 0;
	ssize_t fileDescriptor, readLength, fileSize = 0;
	struct stat fileStatus;
	char *buffer = NULL, *fileName = obtainHistoryFile(info);

	if (!fileName)
		return (0);

	fileDescriptor = open(fileName, O_RDONLY);
	free(fileName);

	if (fileDescriptor == -1)
		return (0);

	if (!fstat(fileDescriptor, &fileStatus))
		fileSize = fileStatus.st_size;

	if (fileSize < 2)
		return (0);

	buffer = malloc(sizeof(char) * (fileSize + 1));

	if (!buffer)
		return (0);

	readLength = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = '\0';

	if (readLength <= 0)
		return (free(buffer), 0);

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			buildHistoryList(info, buffer + last, lineCount++);
			last = i + 1;
		}
	}

	if (last != i)
		buildHistoryList(info, buffer + last, lineCount++);

	free(buffer);
	info->histCount = lineCount;

	while (info->histCount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	renumberHistory(info);
	return (info->histCount);
}

/**
 * buildHistoryList - appends an entry to a history linked list
 * @info: parameter structure
 * @buffer: buffer
 * @lineCount: the history line count
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buffer, int lineCount)
{
	list_t *currentNode = NULL;

	if (info->history)
		currentNode = info->history;

	addNodeEnd(&currentNode, buffer, lineCount);

	if (!info->history)
		info->history = currentNode;

	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: parameter structure
 *
 * Return: the new history count
 */
int renumberHistory(info_t *info)
{
	list_t *currentNode = info->history;
	int i = 0;

	while (currentNode)
	{
		currentNode->num = i++;
		currentNode = currentNode->next;
	}

	return (info->histCount = i);
}

