#include "shell.h"

/**
 * fillMemory - sets a constant byte in a memory block
 * @memoryBlock: pointer to the memory area
 * @byte: the byte to fill @memoryBlock with
 * @size: the number of bytes to fill
 *
 * Return: a pointer to the filled memory area
 */
char *fillMemory(char *memoryBlock, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memoryBlock[i] = byte;
	return memoryBlock;
}

/**
 * freeStringArray - releases memory allocated for an array of strings
 * @stringArray: array of strings
 */
void freeStringArray(char **stringArray)
{
	char **tempArray = stringArray;

	if (!stringArray)
		return;

	while (*stringArray)
		free(*stringArray++);
	free(tempArray);
}

/**
 * reallocateMemory - reallocates a memory block
 * @previousBlock: pointer to the previously allocated block
 * @oldSize: byte size of the previous block
 * @newSize: byte size of the new block
 *
 * Return: pointer to the reallocated block
 */
void *reallocateMemory(void *previousBlock, unsigned int oldSize, unsigned int newSize)
{
	char *newBlock;

	if (!previousBlock)
		return malloc(newSize);

	if (!newSize)
		return free(previousBlock), NULL;

	if (newSize == oldSize)
		return previousBlock;

	newBlock = malloc(newSize);

	if (!newBlock)
		return NULL;

	oldSize = oldSize < newSize ? oldSize : newSize;

	while (oldSize--)
		newBlock[oldSize] = ((char *)previousBlock)[oldSize];

	free(previousBlock);
	return newBlock;
}

