#include "main.h"

/**
 * tokenize - build an array of tokens (strings)
 * @str: string to tokenize
 * @delim: string representing possible delimiters
 * Return: array of strings (needs to be freed)
*/
char **tokenize(char *str, char *delim)
{
        int n_tokens, i;
        char **tokens;
        char *new_str;

        new_str = _strdupp(str);
        n_tokens = count_tokens(str, delim);

        /* allocate a list of pointers with additional space for NULL */
        tokens = malloc((n_tokens + 1) * sizeof(char *));
        tokens[n_tokens] = NULL;

        /* as long we have tokens, take up the first one */
        if (n_tokens > 0)
                tokens[0] = strtok(new_str, delim);
        /* then we keep on tokenizing the same string for the rest */
        for (i = 1; i < n_tokens; i++)
                tokens[i] = strtok(NULL, delim);

        return (tokens);
}


/**
 * count_tokens - counts the number of tokens in a string
 * @str: string to count tokens in
 * @delim: string representing possible delimiters
 * Return: number of tokens found
 */
int count_tokens(char *str, char *delim)
{
        /* started is a flag that we have a current token */
        int i, n = 0, started;

        for (i = started = 0; str[i] != '\0'; i++)
        {
                /* if we found a delimiter and we had a token */
                if (is_delim(str[i], delim) && started)
                {
                        started = 0;
                }
                /* if current is a valid token character and we at its beginning */
                else if (!is_delim(str[i], delim) && !started)
                {
                        started = 1;
                        n++;
                }
        }

        return (n);
}


/**
 * is_delim - check if a given character is a dekimiter or not
 * @c: character to check
 * @delim: string representing possible delimiters
 * Return: 1 if it is. 0 otherwise
 */
bool is_delim(char c, char *delim)
{
        int i;

        for (i = 0; delim[i] != '\0'; i++)
                if (c == delim[i])
                        return (true);
        return (false);
}


/**
 * free_tokens - free a list of strings
 * @tokens: list to free
 */
void free_tokens(char **tokens)
{
        int i;

        for (i = 0; tokens[i] != NULL; i++)
                free(tokens[i]);
        free(tokens);
}
