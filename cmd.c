#include "main.h"

/**
 * cmd_is - check that two strings match
 * used to check the command is a specific builtin
 * @cmd: command string
 * @s: command that we check for
 * Return: 1 if they are equal, 0 otherwise
 */
bool cmd_is(char *cmd, char *s)
{
        int i;

        if (cmd == NULL || s == NULL)
                return (false);

        for (i = 0; s[i] != '\0' && cmd[i] != '\0'; i++)
                if (cmd[i] != s[i])
                        return (false);

        return (cmd[i] == s[i]);
}


/**
 * cmd_exists - checks that a command can be performed
 *  access() is used with the F_OK flag to see if a file exists
 * @cmd: name of program/command
 * Return: 1 if it exists, 0 otherwise
 */
bool cmd_exists(char *cmd)
{
        int i;
        char *trial;

        /* if it's exists without adding it to any of path */
        if (access(cmd, F_OK) == 0)
                return (true);

        /* try adding it to every path and see if it exists then */
        for (i = 0; paths[i] != NULL; i++)
        {
                trial = path_join(paths[i], cmd);
                if (access(trial, F_OK) == 0)
                {
                        free(trial);
                        return (true);
                }
                free(trial);
	}
	return (false);
}
