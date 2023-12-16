#include "shell.h"

/**
 * substituteVariables - substitutes variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substituteVariables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replaceString(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}

