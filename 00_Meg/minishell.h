#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_files
{
    char *value;
    struct s_files *next;
} t_files;

typedef enum token_type
{
    WORD, //general, being replaced after parsing
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    CMD, //echo cat ls
    ARG, //-n file.c
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
    t_files         *lst;
    int             has_leading_space;
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char	**argv;
	char	*infile;
	char	*outfile;
	int		argc;
	int		append;
	int		heredoc;
	t_token_type	connector;
    struct s_cmd    *next;
} t_cmd;

typedef struct s_cmd_list
{
	t_cmd	*head;
	t_cmd	*curr;
} t_cmd_list;

//main.c
char *readline(const char *prompt);
void clean_exit(t_token **token);

//copy_env.c
t_files *cp_env(char **envp);

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
void parsing(t_token **lst, t_files *env);
void update_token(t_token **lst, char *str, char *quote_pos, t_token_type type);
void if_cmd(t_token **lst);
int if_alnum_underscore_braces(int arg);

//parse_var.c
void parse_type_var(t_token **lst, t_token **cur_token, t_files *env);
void expand_var(t_token **lst, t_token **cur_token, t_files *env);

//parse_word.c
void parse_type_word(t_token **cur_token);
void var_found(t_token **cur_token);

//parse_quote.c
void parse_type_quote(t_token **lst, t_token **cur_token, t_files *env);

//parse_arg.c
void parse_type_arg(t_token **lst, t_token **cur_token);

//lst_remove_token.c
void    lst_rm_token(t_token **lst, t_token **cur_token);

//03_builtin
char *cmd_pwd(t_files *env);
void    cmd_export(char *str, t_files **env);


//04_bonus_wildcard
void   expand_wildcard(t_token **cur_token);
void fetch_wildcard(t_files **fn);
bool if_wildcard(t_token **cur_token);
void fn_match_util(char **arr, t_files **fn_lst, t_files **result);
void fn_match(t_files *fn_lst, char *value, t_files **result);
char **append_arr(char **arr, char *str);
char **prepend_arr(char **arr, char *str);
void free_arr(char **arr);
void indir_lst_addback(t_files **lst, t_files *new);

# endif