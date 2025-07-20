/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:28:07 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/20 12:53:44 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_files
{
	char			*value;
	struct s_files	*next;
}	t_files;

typedef enum token_type
{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	CMD,
	ARG,
	PIPE,
	REDIRECT,
	RE_TARGET,
	OR,
	AND,
	WILDCARD,
	ENV_VAR,
	PID,
	EXIT_CODE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_files			*lst;
	int				has_leading_space;
	int				in_quote;
	struct s_token	*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_t;

typedef struct s_redir
{
	t_redir_t		type;
	char			*filename;
	int				in_quote;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				*expand;
	t_redir			*redir_list;
	t_token_type	connector;
	int				argc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec_data
{
	int		*pipe_fds;
	int		num_cmds;
	int		num_pids;
	int		status;
	pid_t	pid[128];
}	t_exec_data;

typedef struct s_hd_data
{
	char	*line;
	char	*delimiter;
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		write;
}	t_hd_data;

//main.c
char		*readline(const char *prompt);
void		clean_exit(t_token **token);

//copy_env.c
t_files		*cp_env(char **envp);
void		update_env(char *value, t_files **env);
void		free_lst(t_files **lst);

//tokenizer.c
t_token		*tokenizer(char *input);
int			delimiter_found(int *in_t, char **input, char **start, t_token **h);

//tokenizer_input.c
int			parse_input(char **input, t_token **head, int *in_token, char **s);

//create_token.c
void		create_token(char **s, char *end, t_token_type t, t_token **lst);

//tokenizer_util.c
char		*ft_strcpy(char *start, char *end);
void		lstadd_back(t_token **lst, t_token *new);
bool		ch_is_space(char ch);
bool		ch_is_special(char ch);
bool		space_special(char ch);

// parsing
int			parsing(t_token **lst, t_files *env, int *exit_status);

//if_cmd.c
int			if_cmd(t_token **lst);
int			if_alnum_underscore_braces(int arg);

//update_token.c
int			update_token(t_token **lst, char *str, char *pos, t_token_type t);

//parse_var.c
int			parse_type_var(t_token **lst, t_token **cur_token, t_files *env);
void		expand_var(t_token **lst, t_token **cur_token, t_files *env);
char		*get_var_value(char *var, t_files *env);
void		if_braces(char **var);
int			parse_type_var_util(char *v, t_files *e, t_token **t, t_token **l);
int			skip_expansion(t_token **lst, t_token **cur_token);

//if_exit_code.c
int			if_exit_code(t_token **cur_token);
void		check_prev_exitcode(t_token **lst, t_token **cur_token);

//expand_var_quotes.c
void		expand_var_quotes(t_token **lst, t_token **cur, t_files *env);
char		*get_var_value(char *var, t_files *env);

//expand_var_heredoc.c
void		expand_var_heredoc(char **line, int exit_status, t_files *env);

//update_var_value.c
void		update_line(char **line, t_files **lst);
void		update_var_value(char **var, t_files *env, t_files **lst);

//parse_word.c
void		parse_type_word(t_token **cur_token);
int			var_found(t_token **lst, t_token **cur_token);

//parse_quote.c
int			parse_type_quote(t_token **lst, t_token **cur_token);

//parse_quote_util.c
void		remove_inner_quote(t_token **cur_token, char quote);
int			after_export(t_token **lst, t_token **cur_token);
int			var_before_quote(t_token **lst, t_token **cur, t_token_type type);

//parse_arg.c
int			parse_type_arg(t_token **lst, t_token **cur_token);
int			join_token(t_token **prev, t_token **cur_token);
//lst_remove_token.c
int			lst_rm_token(t_token **lst, t_token **cur_token);

//add_node_to_lst
void		add_node_to_lst(char *str, int *start, int *end, t_files **lst);
void		add_expanded_var_to_lst(char *value, t_files **lst);
char		*ft_strjoin_free(char *s1, char *s2, size_t len2);

//clear_token.c
void		clear_token(t_token **token);

//handle_sigint.c
void		handle_sigint(int sig);
int			exit_no_input(int *exit_status, t_files **env);

//build_cmds
int			is_connector(t_token_type type);
t_cmd		*build_cmds(t_token *tokens);
void		free_cmd_list(t_cmd *cmd);

//build_cmd_utils.c
t_redir_t	token_to_redir_type(const char *op);
void		free_cmd(t_cmd *cmd);

//expand_exit_status
void		expand_pipeline_exit_status(t_cmd *cmd, int exit_status);

//expand_exit_code.c
char		*expand_exit_code(const char *str, const char *status_str);

//redirections.c
int			redirect_io(t_redir *lst, t_files *env, int *exit_status);
int			check_files(t_redir *list);
int			create_pipes(t_exec_data *data, int num_cmds);
void		redir_pipes(t_exec_data *data, t_files **env);

//heredoc.c
int			pipe_heredoc(char *delim, t_files *env, int status, int in_quote);
int			fork_heredoc(char *delimiter);

//exec_commands
void		exec_commands(t_cmd *cmd_list, t_files **env, int *exit_status);
int			process_all_heredocs(t_cmd *cmd_list, int *exit_status);

//exec_utils
int			count_pipeline_cmds(t_cmd *cmd);
void		close_pipes(t_exec_data *data);
int			wait_pids(t_exec_data *data);
void		exit_child(char *msg, t_exec_data *data, t_files **env);

//exec_builtins
int			exec_builtin(t_cmd *cmds, t_cmd *cmd, t_files **env, int status);
int			exec_builtin_no_output(t_cmd *cs, t_cmd *c, t_files **env, int s);
int			is_builtin(t_cmd *cmd);
int			is_builtin_without_output(t_cmd *cmd);

//command
void		exec_command(char **cmd_args, t_files *env);

//03_builtin
int			cmd_exit(t_cmd *cmd_list, t_cmd *cmd, t_files **env, int status);
int			cmd_pwd(t_files *env);
int			cmd_export(char *str, t_files **env);
char		*dequote_str_export(char *pos);
bool		if_replace(char *str, t_files **env);
int			declare_env(t_files *env);
int			if_append_var(char *str, char *pos, t_files **env);
int			declare_env(t_files *env);
int			cmd_env(t_files *env);
int			cmd_unset(char *var, t_files **env);
char		*ft_strndup(char *src, int len);
void		lstadd_start(t_files **env, char *str);
int			cmd_echo(char **argv);
int			cmd_cd(char *str, t_files **env);
void		print_error(char *str);

//04_bonus_wildcard
void		update_result(char *value, t_files **result, int *flag);
int			expand_wildcard(t_token **lst, t_token **cur_token);
void		init_fn_lst(t_files **fn_lst);
bool		if_wildcard(t_token **cur_token);
char		*strmatch(const char *big, const char *little);
void		fn_match_util(char **arr, t_files **fn_lst, t_files **result);
void		fn_match(t_files *fn_lst, char *value, t_files **result);
char		**append_arr(char **arr);
char		**prepend_arr(char **arr, char *value);
void		free_arr(char **arr);
void		indir_lst_addback(t_files **lst, t_files *new);
void		add_wildcard_token(t_token **lst, t_token *curr, t_files *files);
t_files		*duplicate_fn_lst(t_files *lst);

void		if_end_to_match(char **arr, int *flag);
void		free_arr(char **arr);

void		execution(t_token **token, t_files **env, int *exit_status);

#endif
