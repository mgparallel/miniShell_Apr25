#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_files_indir
{
    char *value;
    struct s_files_indir *next;
} t_files_indir;

typedef enum token_type
{
    WORD, //general, being replaced after parsing
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    COMMAND, //echo cat ls
    ARGUMENT, //-n file.c
    EXIT_CODE, //$?
    PIPE, //  |
    REDIRECTION, //< > << >>
    RE_TARGET,
    LOGICAL_OR, // ||
    LOGICAL_AND, // &&
    WILDCARD, //*
    ENV_VARIABLE, //$
    PID, //$$
} t_token_type;

// typedef struct s_cmd
// {
//     char *path;
//     char **argv;
// } t_cmd;

// typedef struct 
// {
// 	int infile;
// 	int outfile;
// 	int pipe_in[2];
// 	int pipe_out[2];
// 	char *cmd;
// };

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
void fetch_wildcard(t_files_indir **fn);
bool if_wildcard(t_token **cur_token);

void	lstadd_back(t_token **lst, t_token *new);

void clean_exit(t_token **token);


void fn_match_util(char **arr, t_files_indir **fn_lst, t_files_indir **result);
void fn_match(t_files_indir *fn_lst, char *value, t_files_indir **result);
char **append_arr(char **arr, char *str);
char **prepend_arr(char **arr, char *str);
void free_arr(char **arr);

# endif