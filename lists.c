#include "shell.h"

/**
 * prependNode - adds a node to the beginning of the list
 * @head: address of pointer to the head node
 * @str: string field of the node
 * @num: index used by history
 *
 * Return: pointer to the new head of the list
 */
list_t *prependNode(list_t **head, const char *str, int num)
{
	list_t *newHead;

	if (!head)
		return (NULL);

	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);

	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = num;

	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}

	newHead->next = *head;
	*head = newHead;

	return newHead;
}

/**
 * appendNode - adds a node to the end of the list
 * @head: address of pointer to the head node
 * @str: string field of the node
 * @num: index used by history
 *
 * Return: pointer to the new node added at the end
 */
list_t *appendNode(list_t **head, const char *str, int num)
{
	list_t *newNode, *currentNode;

	if (!head)
		return (NULL);

	currentNode = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	if (currentNode)
	{
		while (currentNode->next)
			currentNode = currentNode->next;
		currentNode->next = newNode;
	}
	else
		*head = newNode;

	return newNode;
}

/**
 * printStringList - prints only the string element of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: number of nodes in the list
 */
size_t printStringList(const list_t *head)
{
	size_t nodeCount = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		nodeCount++;
	}

	return nodeCount;
}

/**
 * deleteNodeAtIndex - deletes a node at the given index
 * @head: address of pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *currentNode, *previousNode;
	unsigned int currentIndex = 0;

	if (!head || !*head)
		return 0;

	if (!index)
	{
		currentNode = *head;
		*head = (*head)->next;
		free(currentNode->str);
		free(currentNode);
		return 1;
	}

	currentNode = *head;

	while (currentNode)
	{
		if (currentIndex == index)
		{
			previousNode->next = currentNode->next;
			free(currentNode->str);
			free(currentNode);
			return 1;
		}

		currentIndex++;
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	return 0;
}

/**
 * freeStringList - frees all nodes of a list
 * @headPointer: address of pointer to the head node
 *
 * Return: void
 */
void freeStringList(list_t **headPointer)
{
	list_t *currentNode, *nextNode, *head;

	if (!headPointer || !*headPointer)
		return;

	head = *headPointer;
	currentNode = head;

	while (currentNode)
	{
		nextNode = currentNode->next;
		free(currentNode->str);
		free(currentNode);
		currentNode = nextNode;
	}

	*headPointer = NULL;
}

