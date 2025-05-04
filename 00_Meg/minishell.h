#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef enum token_type
{
    WORD, //general, can be COMMAND 
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    COMMAND, //echo cat ls
    ARGUMENT, //-n file.c
    EXIT_CODE,
    PIPE,
    REDIRECTION, //< > << >>
    RE_TARGET,
    LOGICAL_OR, // ||
    LOGICAL_AND, // &&
    WILDCARD, //*
    ENV_VARIABLE, //$
    PID, //$$
} t_token_type;

typedef struct s_cmd
{
    char *path;
    char **argv;
} t_cmd;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    int             has_leading_space;
    struct s_token *next;
} t_token;

char *readline(const char *prompt);
bool ch_is_space(char ch);
char *ft_strcpy(char *start, char *end);
t_token *tokenizer(char *input);
void create_token(char **start, char *end, t_token_type type, t_token **lst);

void parsing(t_token **lst);
int if_alnum_underscore(int arg);

void	lstadd_back(t_token **lst, t_token *new);

# endif