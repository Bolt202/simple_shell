#include "shell.h"

/**
 * acquireEnvironment - obtains a copy of the environment as a string array
 * @info: Structure that may contain arguments. Maintained for consistent
 *        function prototype.
 * Return: Always 0
 */
char **acquireEnvironment(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = convertListToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environ);
}

/**
 * abolishEnvVariable - Eliminate an environment variable
 * @info: Structure that may contain arguments. Maintained for consistent
 *        function prototype.
 * Return: 1 on deletion, 0 otherwise
 * @var: the string property of the environment variable
 */
int abolishEnvVariable(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = findPrefix(node->str, var);
		if (p && *p == '=')
		{
			info->envChanged = removeNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envChanged);
}

/**
 * establishEnvVariable - Create a new environment variable or modify an existing one
 * @info: Structure that may contain arguments. Maintained for consistent
 *        function prototype.
 * @var: the string property of the environment variable
 * @value: the string value of the environment variable
 * Return: Always 0
 */
int establishEnvVariable(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = allocateMemory(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = findPrefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	appendNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}

