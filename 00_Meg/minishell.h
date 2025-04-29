#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
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
    PIPE,
    REDIRECTION, //< > << >>
    LOGICAL_OR, // ||
    LOGICAL_AND, // &&
    SPECIAL, //$, $$
    ENV_VARIABLE, //$
} t_token_type;

// typedef struct s_index
// {
//     char *start;
//     char *end;
// } t_index;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token *next;
} t_token;

char *readline (const char *prompt);
t_token *tokenizer(char *input);
void create_token(char **start, char *end, t_token_type type, t_token **lst);

# endif