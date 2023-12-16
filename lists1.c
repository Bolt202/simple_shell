#include "shell.h"

/**
 * determineListLength - calculates the length of a linked list
 * @currentNode: pointer to the first node
 *
 * Return: size of the list
 */
size_t determineListLength(const list_t *currentNode)
{
	size_t count = 0;

	while (currentNode)
	{
		currentNode = currentNode->next;
		count++;
	}
	return count;
}

/**
 * convertListToStrings - transforms a linked list into an array of strings
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **convertListToStrings(list_t *head)
{
	list_t *currentNode = head;
	size_t length = determineListLength(head), index;
	char **stringArray;
	char *string;

	if (!head || !length)
		return NULL;

	stringArray = malloc(sizeof(char *) * (length + 1));

	if (!stringArray)
		return NULL;

	for (index = 0; currentNode; currentNode = currentNode->next, index++)
	{
		string = malloc(_strlen(currentNode->str) + 1);

		if (!string)
		{
			for (size_t j = 0; j < index; j++)
				free(stringArray[j]);
			free(stringArray);
			return NULL;
		}

		_strcpy(string, currentNode->str);
		stringArray[index] = string;
	}

	stringArray[index] = NULL;
	return stringArray;
}

/**
 * displayList - prints all elements of a list_t linked list
 * @currentNode: pointer to the first node
 *
 * Return: size of the list
 */
size_t displayList(const list_t *currentNode)
{
	size_t count = 0;

	while (currentNode)
	{
		_puts(convert_number(currentNode->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(currentNode->str ? currentNode->str : "(nil)");
		_puts("\n");
		currentNode = currentNode->next;
		count++;
	}
	return count;
}

/**
 * findNodeWithPrefix - locates a node whose string starts with a given prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @nextChar: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *findNodeWithPrefix(list_t *node, char *prefix, char nextChar)
{
	char *matchingPrefix = NULL;

	while (node)
	{
		matchingPrefix = starts_with(node->str, prefix);

		if (matchingPrefix && ((nextChar == -1) || (*matchingPrefix == nextChar)))
			return node;

		node = node->next;
	}
	return NULL;
}

/**
 * getNodeIndex - retrieves the index of a node
 * @head: pointer to the list head
 * @targetNode: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t getNodeIndex(list_t *head, list_t *targetNode)
{
	size_t index = 0;

	while (head)
	{
		if (head == targetNode)
			return index;

		head = head->next;
		index++;
	}
	return -1;
}

