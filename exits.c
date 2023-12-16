#include "shell.h"

/**
 * _custom_strncpy - Copies a string up to a specified length.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_length: The maximum number of characters to be copied.
 * Return: The resulting string.
 */
char *_custom_strncpy(char *destination, char *source, int max_length)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < max_length - 1)
    {
        destination[i] = source[i];
        i++;
    }

    if (i < max_length)
    {
        j = i;
        while (j < max_length)
        {
            destination[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * _custom_strncat - Concatenates two strings up to a specified length.
 * @destination: The first string.
 * @source: The second string.
 * @max_length: The maximum number of bytes to be used.
 * Return: The resulting concatenated string.
 */
char *_custom_strncat(char *destination, char *source, int max_length)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;

    while (destination[i] != '\0')
        i++;

    while (source[j] != '\0' && j < max_length)
    {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < max_length)
        destination[i] = '\0';

    return result;
}

/**
 * _custom_strchr - Locates a character in a string.
 * @str: The string to be parsed.
 * @character: The character to look for.
 * Return: A pointer to the memory area within the string.
 */
char *_custom_strchr(char *str, char character)
{
    do
    {
        if (*str == character)
            return str;
    } while (*str++ != '\0');

    return NULL;
}

