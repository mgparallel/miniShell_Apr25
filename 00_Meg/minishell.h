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
    COMMAND, //echo cat ls
    ARGUMENT, //-n file.c
    PIPE, 
    SIGNAL, 
    REDIRECTION, //< > << >>
    ENV_VARIABLE, //&
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char    *value;
} t_token;

char *readline (const char *prompt);
t_token **tokenizer(char *input);


# endif