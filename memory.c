#include "shell.h"

/**
 * freeAndNull - deallocates memory and sets the pointer to NULL
 * @pointerAddress: address of the pointer to be freed
 *
 * Return: 1 if memory was freed, otherwise 0.
 */
int freeAndNull(void **pointerAddress)
{
	if (pointerAddress && *pointerAddress)
	{
		free(*pointerAddress);
		*pointerAddress = NULL;
		return 1;
	}
	return 0;
}


