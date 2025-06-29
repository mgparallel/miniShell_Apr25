#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
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
	EXIT_CODE,
} t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    t_files         *lst;
    int             has_leading_space;
    struct s_token *next;
} t_token;

typedef enum e_redir_type
{
    REDIR_INPUT,      // <
    REDIR_OUTPUT,     // >
    REDIR_APPEND,     // >>
    REDIR_HEREDOC     // <<
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;
    char            *filename;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
	char	        **argv;
	t_redir         *redir_list;
	int		        argc;
	t_token_type    connector;
    struct s_cmd    *next;
} t_cmd;

typedef struct s_exec_data
{
	int		*pipe_fds;
	int		num_pids;
	pid_t	pid[128];
} t_exec_data;

//main.c
char *readline(const char *prompt);
void clean_exit(t_token **token);

//copy_env.c
t_files *cp_env(char **envp);
void update_env(char *value, t_files **env);
void free_lst(t_files **lst);

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
void if_cmd(t_token **lst);
int if_alnum_underscore_braces(int arg);

//update_token.c
void update_token(t_token **lst, char *str, char *quote_pos, t_token_type type);

//parse_var.c
int parse_type_var(t_token **lst, t_token **cur_token, t_files *env);
void expand_var(t_token **lst, t_token **cur_token, t_files *env);
char *get_var_value(char *var, t_files *env);
void if_braces(char **var);
int parse_type_var_util(char *var, t_files *env, t_token **cur_token, t_token **lst);

//if_exit_code.c
int if_exit_code(t_token **cur_token);
void    check_prev_exitcode(t_token **lst, t_token **cur_token);

//expand_var_quotes.c
void expand_var_quotes(t_token **lst, t_token **cur_token, t_files *env);
char *get_var_value(char *var, t_files *env);

//expand_var_heredoc.c
void	expand_var_heredoc(char **line, int exit_status, t_files *env);

//parse_word.c
void parse_type_word(t_token **cur_token);
void var_found(t_token **cur_token);

//parse_quote.c
void parse_type_quote(t_token **cur_token);

//parse_arg.c
void parse_type_arg(t_token **lst, t_token **cur_token);
void    join_token(t_token **prev, t_token **cur_token);
//lst_remove_token.c
int    lst_rm_token(t_token **lst, t_token **cur_token);

//add_node_to_lst
void add_node_to_lst(char *str, int *start, int *end, t_files **lst);
void	add_expanded_var_to_lst(char *value, t_files **lst);
char *ft_strjoin_free(char *s1, char *s2, size_t len2);

//build_cmds
int is_connector(t_token_type type);
t_cmd   *build_cmds(t_token *tokens);
void    free_cmd_list(t_cmd *cmd);

//exec_commands
void    exec_commands(t_cmd *cmd_list, t_files **env, int *exit_status);
int check_files(t_redir *list);
int cmd_exit(t_cmd *cmd, int is_child);

//exec utils
int exec_builtin(t_cmd *cmd, t_files **env, int is_child);
int exec_builtin_without_output(t_cmd *cmd, t_files **env, int is_child);
int is_builtin(t_cmd *cmd);
int is_builtin_without_output(t_cmd *cmd);;
void    exec_command(char **cmd_args, t_files *env);

//03_builtin
int     cmd_pwd(t_files *env);
int     cmd_export(char *str, t_files **env);
int		declare_env(t_files *env);
int     cmd_env(t_files *env);
int     cmd_unset(char *var, t_files **env);
char *ft_strndup(char *src, int len);
void    lstadd_start(t_files **env, char *str);
int     cmd_echo(char **argv);
int     cmd_cd(char *str, t_files **env);

//04_bonus_wildcard
void   expand_wildcard(t_token **lst, t_token **cur_token);
void fetch_wildcard(t_files **fn);
bool if_wildcard(t_token **cur_token);
void fn_match_util(char **arr, t_files **fn_lst, t_files **result);
void fn_match(t_files *fn_lst, char *value, t_files **result);
char **append_arr(char **arr, char *str);
char **prepend_arr(char **arr, char *value, char *str);
void free_arr(char **arr);
void indir_lst_addback(t_files **lst, t_files *new);
void add_wildcard_token(t_token **lst, t_token *curr, t_files *files);

# endif