#include "shell.h"

/**
 * copyString - copies the content of one string to another
 * @destination: the destination string
 * @source: the source string
 *
 * Return: a pointer to the destination string
 */
char *copyString(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return destination;

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';
	return destination;
}

/**
 * duplicateString - duplicates a given string
 * @str: the string to duplicate
 *
 * Return: a pointer to the duplicated string
 */
char *duplicateString(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return NULL;

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return NULL;

	for (length++; length--;)
		result[length] = *--str;

	return result;
}

/**
 * printString - prints a given string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		printCharacter(str[index]);
		index++;
	}
}

/**
 * printCharacter - writes the character to the standard output
 * @character: The character to print
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharacter(char character)
{
	static int bufferIndex;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUF_FLUSH || bufferIndex >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, bufferIndex);
		bufferIndex = 0;
	}

	if (character != BUF_FLUSH)
		buffer[bufferIndex++] = character;

	return 1;
}

