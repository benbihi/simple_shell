#include "main.h"


/**
 * _strdupp - duplicate a string
 * @s: the string
 * Return: the new duplicated string (needs to be freed)
 */
char *_strdupp(char *s)
{
        int i;
        char *new = malloc((_strlen(s) + 1) * sizeof(char));

        for (i = 0; s[i] != '\0'; i++)
                new[i] = s[i];
        new[i] = '\0';

        return (new);
}


/**
 * _strlen - count length of a string
 * @s: string to count
 * Return: length of string
 */
int _strlen(char *s)
{
        int n = 0;

        while (s[n] != '\0')
                n++;

        return (n);
}


/**
 * _puts - prints a given string followed by a new line
 * @s: string to print
 */
void _puts(char *s)
{
        int i;

        for (i = 0; s[i] != '\0'; i++)
                write(STDOUT_FILENO, &s[i], 1);

        write(STDOUT_FILENO, "\n", 1);
}


/**
 * path_join - concatenates two strings with '/' in between
 * @dir: left string; the directory path
 * @file: right string; the file name
 * Return: newly created concat string (needs to be freed)
 */
char *path_join(char *dir, char *file)
{
        int i = 0, j;
        /* allocate space for both strings and '/' and NULL */
        char *full = malloc((_strlen(dir) + _strlen(file) + 2) * sizeof(char));

        /* copy first string */
        for (j = 0; dir[j] != '\0'; i++, j++)
                full[i] = dir[j];
        /* add the slash */
        full[i++] = '/';
        /* copy the second string */
        for (j = 0; file[j] != '\0'; i++, j++)
                full[i] = file[j];
        /* add the NULL */
        full[i++] = '\0';

        return (full);
}


/**
 * starts_with - checks whether a given string starts with a given value
 * @s: the asked string
 * @prefix: value to check against
 * Return: 1 if matched, 0 otherwise
 */
bool starts_with(char *s, char *prefix)
{
        int i;

        /* make sure nothing is NULL */
        if (s == NULL || prefix == NULL)
                return (false);

        /* go through the strings */
        for (i = 0; prefix[i] != '\0' && s[i] != '\0'; i++)
                /* if at least 1 letter do not match, return false */
                if (s[i] != prefix[i])
                        return (false);

        /* make sure the prefix was checked to the end */
        return (prefix[i] == '\0');
}
