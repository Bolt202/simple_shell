#include "shell.h"

/**
 * initializeInfo - sets up the info_t structure
 * @info: pointer to the structure
 */
void initializeInfo(info_t *info)
{
	info->argument = NULL;
	info->arguments = NULL;
	info->executablePath = NULL;
	info->argumentCount = 0;
}

/**
 * configureInfo - configures the info_t structure
 * @info: pointer to the structure
 * @argumentVector: array of arguments
 */
void configureInfo(info_t *info, char **argumentVector)
{
	int index = 0;

	info->programName = argumentVector[0];
	if (info->argument)
	{
		info->arguments = tokenizeString(info->argument, " \t");
		if (!info->arguments)
		{
			info->arguments = malloc(sizeof(char *) * 2);
			if (info->arguments)
			{
				info->arguments[0] = duplicateString(info->argument);
				info->arguments[1] = NULL;
			}
		}
		for (index = 0; info->arguments && info->arguments[index]; index++)
			;
		info->argumentCount = index;

		applyAlias(info);
		applyVariableReplacements(info);
	}
}

/**
 * releaseInfo - deallocates memory associated with info_t structure fields
 * @info: pointer to the structure
 * @releaseAll: true if releasing all fields
 */
void releaseInfo(info_t *info, int releaseAll)
{
	freeMemory(info->arguments);
	info->arguments = NULL;
	info->executablePath = NULL;
	if (releaseAll)
	{
		if (!info->commandBuffer)
			free(info->argument);
		if (info->environment)
			freeList(&(info->environment));
		if (info->commandHistory)
			freeList(&(info->commandHistory));
		if (info->aliasList)
			freeList(&(info->aliasList));
		freeMemory(info->environmentVariables);
		info->environmentVariables = NULL;
		blockFree((void **)info->commandBuffer);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		writeCharacterToStandardOutput(BUFFER_FLUSH);
	}
}

