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
    CMD, //echo cat ls
    ARG, //-n file.c
    EXIT_CODE, //$?
    PIPE, //  |
    REDIRECT, //< > << >>
    RE_TARGET,
    OR, // ||
    AND, // &&
    WILDCARD, //*
    ENV_VAR, //$
    PID, //$$
} t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    int             has_leading_space;
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	t_token *tokens;
    struct s_cmd    *next;
} t_cmd;

//main.c
char *readline(const char *prompt);
void clean_exit(t_token **token);

//tokenizer.c
t_token *tokenizer(char *input);
int	delimiter_found(int *in_token, char **input, char **token_start, t_token **head);

//tokenizer_input.c
int parse_input(char **input, t_token **head, int *in_token, char **token_start);

//tokenizer_util.c
void create_token(char **start, char *end, t_token_type type, t_token **lst);
char *ft_strcpy(char *start, char *end);
void	lstadd_back(t_token **lst, t_token *new);
bool ch_is_space(char ch);
bool ch_is_special(char ch);

// parsing
void parsing(t_token **lst);
void update_token(t_token **lst, char *str, char *quote_pos, t_token_type type);
void if_cmd(t_token **lst);
int if_alnum_underscore_braces(int arg);

//parse_var.c
void parse_type_var(t_token **cur_token);
void expand_var(t_token **cur_token, char *pos);

//parse_word.c
void parse_type_word(t_token **cur_token);
void var_found(t_token **cur_token);

//parse_quote.c
void parse_type_quote(t_token **cur_token);

//parse_arg.c
void parse_type_arg(t_token **lst, t_token **cur_token);

//04_bonus_wildcard
void fetch_wildcard(t_files_indir **fn);
bool if_wildcard(t_token **cur_token);
void fn_match_util(char **arr, t_files_indir **fn_lst, t_files_indir **result);
void fn_match(t_files_indir *fn_lst, char *value, t_files_indir **result);
char **append_arr(char **arr, char *str);
char **prepend_arr(char **arr, char *str);
void free_arr(char **arr);

# endif