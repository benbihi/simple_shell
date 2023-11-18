#include "main.h"


/**
 * _get_env - return a reference to the value
 *  of a specific variable in te environment
 * @name: name of the wanted variable
 * Return: pointer to the start of its value
 */
char *_get_env(char *name)
{
        int i, len;

        if (name == NULL)
                return (NULL);

        len = _strlen(name);

        /* go through all variables */
        for (i = 0; environ[i] != NULL; i++)
                /* if variable is found */
                if (starts_with(environ[i], name))
                        /* return a pointer to its value (after the =) */
                        return (&environ[i][len + 1]);

        return (NULL);
}


/**
 * print_env - prints the environment variables one by one
 */
void print_env(void)
{
        int i;

        for (i = 0; environ[i] != NULL; i++)
                _puts(environ[i]);
}
