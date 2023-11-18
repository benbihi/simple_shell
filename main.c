#include "main.h"


/**
 * main - simple shell.
 * @argc: arguments count
 * @argv: arguments vector
 * @envp: an optional third parameter to main
 *      holds the environment (list of strings)
 *      where we can find path and execve() needs
 * Return: 0 on success.
 */
int main(__attribute__((unused)) int argc, char *argv[], char *envp[])
{
        /* save needed data for later */
        prog_name = argv[0];
        environ = envp;
        paths = tokenize(_get_env("PATH"), ":");
        exit_flag = false;

        /**
         * if interactive shell/terminal
         *  then we should keep on working and performing commands
         *  until an exit is called.
         * is_atty() is the function that tells us if we are in a terminal
        */
        if (isatty(STDIN_FILENO))
        {
                while (true)
                {
                        /* display prompt */
                        write(STDOUT_FILENO, "> ", 2);
                        get_perform_cmd();
                        /* if exit flag was set */
                        if (exit_flag)
                                break;
                }
        }
        /* if not interactive, (using echo and pipe |), just perform and finish */
        else
        {
                get_perform_cmd();
        }

        free_tokens(paths);
        return (EXIT_SUCCESS);
}

/**
 * get_perform_cmd - get and perform a command
 */
void get_perform_cmd(void)
{
        char *line = NULL;
        size_t len = 0;
        int read;
        char **args;

        /* first, we get the command using getline() */
        read = getline(&line, &len, stdin);
        /* if getline failed e.g. EOF (end_of_file) was there, we end */
        if (read == -1)
        {
            fflush(stdin);
                free(line);
                perror(prog_name);
                return;
        }

        /* let's tokenize the command into args */
        args = tokenize(line, " \t\n");

        /* check for builtins and perform them */
        if (cmd_is(args[0], "exit"))
                exit_flag = true;  /* just mark the exit flag */
        else if (cmd_is(args[0], "env"))
                print_env();

        /* we make sure the command exists. if it fails, we stop */
        else if (!cmd_exists(args[0]))
                perror(prog_name);
        /* now, we're sure that the command exists, so we execute it */
        else
                execute(args);

        free_tokens(args);
        free(line);
}


/**
 * execute - perform the command using execve
 * @args: the command along with arguments if exist
 */
void execute(char **args)
{
        int wstatus = 0, cpid = 0;

        /* we fork the process so that our process remains and program continues */
        cpid = fork();
        if (cpid == -1)
        {
                /* fork was not successful */
                perror("fork");
        }
        else if (cpid == 0)
        {
                /* we're in the child process, so execute */
                execve(args[0],
                        (char * const *) args,
                        (char * const *) environ);
                /* if execve returns, there is something wrong */
                perror(prog_name);
                exit(EXIT_FAILURE);
        }
        else
        {
                /* we're in the main process, so we wait for the child to finish */
                wait(&wstatus);
        }
}
