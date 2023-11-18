#ifndef HSH
#define HSH

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* main execution */
void get_perform_cmd();
void execute(char **args);

/* command */
bool cmd_is(char *cmd, char *s);
bool cmd_exists(char *cmd);

/* tokenizer */
char **tokenize(char *str, char *delim);
int count_tokens(char *str, char *delim);
bool is_delim(char c, char *delim);
void free_tokens(char **tokens);

/* string */
void _puts(char *s);
int _strlen(char *s);
char *_strdupp(char *s);
bool starts_with(char *s, char *prefix);
char *path_join(char *dir, char *file);

/* environ */
char *_get_env(char *name);
void print_env(void);

/* global variables */
char *prog_name;
char **environ;
char **paths;
bool exit_flag;

#endif
