#include "shell.h"

/**
 * bufferInput - manages the buffer for chained commands
 * @info: structure containing parameters
 * @buffer: address of the buffer
 * @length: address of the length variable
 *
 * Return: number of bytes read
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t currentLength = 0;

	if (!*length) /* if the buffer is empty, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(buffer, &currentLength, stdin);
#else
		bytesRead = _getline(info, buffer, &currentLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = bytesRead;
				info->cmd_buf = buffer;
			}
		}
	}
	return bytesRead;
}

/**
 * getInput - obtains a line without the newline character
 * @info: structure containing parameters
 *
 * Return: number of bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t currentIndex, nextIndex, bufferLength;
	ssize_t bytesRead = 0;
	char **bufferPointer = &(info->arg), *currentPointer;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buffer, &bufferLength);
	if (bytesRead == -1) /* EOF */
		return -1;
	if (bufferLength)	/* commands left in the chain buffer */
	{
		nextIndex = currentIndex; /* initialize new iterator to the current buffer position */
		currentPointer = buffer + currentIndex; /* get pointer for return */

		check_chain(info, buffer, &nextIndex, currentIndex, bufferLength);
		while (nextIndex < bufferLength) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &nextIndex))
				break;
			nextIndex++;
		}

		currentIndex = nextIndex + 1; /* increment past nulled ';'' */
		if (currentIndex >= bufferLength) /* reached the end of the buffer? */
		{
			currentIndex = bufferLength = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*bufferPointer = currentPointer; /* pass back pointer to the current command position */
		return _strlen(currentPointer); /* return the length of the current command */
	}

	*bufferPointer = buffer; /* not a chain, pass back buffer from _getline() */
	return bytesRead; /* return the length of the buffer from _getline() */
}

/**
 * readBuffer - reads a buffer
 * @info: structure containing parameters
 * @buffer: buffer
 * @currentIndex: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *currentIndex)
{
	ssize_t bytesRead = 0;

	if (*currentIndex)
		return 0;
	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*currentIndex = bytesRead;
	return bytesRead;
}

/**
 * _getlineImplementation - obtains the next line of input from STDIN
 * @info: structure containing parameters
 * @pointer: address of the pointer to the buffer, preallocated or NULL
 * @length: size of the preallocated buffer if not NULL
 *
 * Return: bytesRead
 */
int _getlineImplementation(info_t *info, char **pointer, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t currentIndex, bufferLength;
	size_t index;
	ssize_t bytesRead = 0, totalBytesRead = 0;
	char *currentPointer = NULL, *newPointer = NULL, *c;

	currentPointer = *pointer;
	if (currentPointer && length)
		totalBytesRead = *length;
	if (currentIndex == bufferLength)
		currentIndex = bufferLength = 0;

	bytesRead = readBuffer(info, buffer, &bufferLength);
	if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
		return -1;

	c = _strchr(buffer + currentIndex, '\n');
	index = c ? 1 + (unsigned int)(c - buffer) : bufferLength;
	newPointer = _realloc(currentPointer, totalBytesRead, totalBytesRead ? totalBytesRead + index : index + 1);
	if (!newPointer) /* MALLOC FAILURE! */
		return (currentPointer ? free(currentPointer), -1 : -1);

	if (totalBytesRead)
		_strncat(newPointer, buffer + currentIndex, index - currentIndex);
	else
		_strncpy(newPointer, buffer + currentIndex, index - currentIndex + 1);

	totalBytesRead += index - currentIndex;
	currentIndex = index;
	currentPointer = newPointer;

	if (length)
		*length = totalBytesRead;
	*pointer = currentPointer;
	return totalBytesRead;
}

/**
 * sigintHandler - handles the SIGINT signal (Ctrl-C)
 * @signalNumber: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

