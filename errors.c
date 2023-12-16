#include "shell.h"

/**
 * _eputs - Outputs a string to the standard error.
 * @str: The string to be printed.
 */
void _eputs(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        _eputchar(str[index]);
        index++;
    }
}

/**
 * _eputchar - Writes a character to the standard error.
 * @c: The character to be printed.
 * Return: On success 1, on error -1.
 */
int _eputchar(char c)
{
    static int currentIndex;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || currentIndex >= WRITE_BUF_SIZE)
    {
        write(2, buffer, currentIndex);
        currentIndex = 0;
    }

    if (c != BUF_FLUSH)
        buffer[currentIndex++] = c;

    return (1);
}

/**
 * _putfd - Writes a character to the given file descriptor.
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 * Return: On success 1, on error -1.
 */
int _putfd(char c, int fd)
{
    static int currentIndex;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || currentIndex >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, currentIndex);
        currentIndex = 0;
    }

    if (c != BUF_FLUSH)
        buffer[currentIndex++] = c;

    return (1);
}

/**
 * _putsfd - Outputs a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int _putsfd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return (0);

    while (*str)
    {
        count += _putfd(*str++, fd);
    }

    return (count);
}

