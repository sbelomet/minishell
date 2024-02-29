/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/29 15:05:58 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>

# include "../libs/ft_printf/libft/libft.h"
# include "../libs/ft_printf/include/ft_printf.h"

# define WHITE "\033[0;39m"
# define B_WHITE "\033[1;39m"

enum e_env_types
{
	NONE,
	BOTH,
	ONLY_ENV,
	ONLY_EXPORT,
	TO_BOTH,
	LIMBO = 666
};

enum e_types
{
	TOKEN_UNKNOWN_REDIR,
	TOKEN_CMD,
	TOKEN_BUILTIN,
	TOKEN_BIN,
	TOKEN_ARG,
	TOKEN_REDIR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APP,
	TOKEN_REDIR_HDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_FILE,
	TOKEN_VAR,
	TOKEN_WORD
};

typedef struct s_token
{
	int				id;
	void			*type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	int				id;
	int				file_fd;
	char			*name;
	char			*limiter;
	char			*filepath;
}					t_redir;

typedef struct s_var
{
	char			*name;
	char			*value;
	int				standalone;
	int				printable;
	struct s_var	*prev;
	struct s_var	*next;
}					t_var;

typedef struct s_arg
{
	int				id;
	int				index;
	char			*name;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_cmd
{
	int				id;
	pid_t			child;
	char			*path;
	int				fd_in;
	int				fd_out;
	char			*name;
	t_arg			*first_arg;
}					t_cmd;

typedef struct s_cmds
{
	t_cmd			*cmd;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_lexvars
{
	int				after_cmd;
	int				after_redir;
}					t_lexvars;

typedef struct s_base
{
	char			**env;
	t_alloc			*alloc;
	char			*curdir;
	t_var			*first_var;
	t_token			*first_token;
	t_lexvars		lexvars;
	int				pipe;
	int				exit_status;
	t_cmds			*cmds;
}					t_base;

int		g_signum;

/* PROMPT */
void	ft_prompt(t_base *base);
int		prompt_cmd(t_base *base);
char	*ft_get_curdir(t_base *base);
char	*ft_format_prompt(t_base *base);
void	ft_free_after_prompt(t_base *base, char *rl, char *line, char *prompt);

/* ERROR */
void	ft_free(t_base base);
int		errors_lexer(t_base *base);
void	ft_error(t_base *base);
int		check_err_token_redirec(t_token *token);
int		error_manager(t_base *base, int status_code,
			char *message, int exit_code);

/* FREEING TOKENS */
void	ft_free_tokens(t_token *first_token);

/* BASE INIT */
void	ft_base_init(t_base *base, char **env);
void	ft_incr_shell_level(t_base *base);

/* SIGNALS UTILS */
void	ft_interactive_signals(void);
void	ft_heredoc_signal(void);
void	ft_merdique_signal(void);
void	ft_ctrl_slash(int signum);
void	ft_ctrl_c1(int signum);
void	ft_ctrl_c2(int signum);
void	ft_ctrl_c3(int signum);

/* GETTERS */
char	*get_current_path(void);
t_arg	*get_first_arg(t_cmd *cmd);
char	*get_home_path(t_base *base);
t_cmd	*get_prev_cmd(t_token *token);
t_cmd	*get_next_cmd(t_token *token);
t_token	*get_first_token(t_base *base);
void	*get_token_class(t_token *token);
t_token	*get_first_builtin(t_base *base);
t_token	*get_next_builtin(t_token *token);
t_token	*get_first_token_cmd(t_base *base);
t_token	*get_next_token_cmd(t_token *token);
t_cmd	*get_prev_cmd_no_skip(t_token *token);
t_cmd	*get_next_cmd_no_skip(t_token *token);
t_token	*get_first_token_cmd_no_skip(t_base *base);

/* CHECKERS */
int		is_cmd_bin(t_cmd *cmd);
int		is_cmd_builtin(t_cmd *cmd);
int		is_numeric_arg(t_arg *arg);
int		is_token_cmd(t_token *token);
int		is_token_bin(t_token *token);
int		is_token_pipe(t_token *token);
int		is_token_file(t_token *token);
int		is_token_redirec(t_token *token);
int		is_token_heredoc(t_token *token);
int		is_token_builtin(t_token *token);
int		is_token_basic_redir(t_token *token);
int		is_builtin_cmd(char *name, t_cmd *cmd);

/* UPDATES */
void	update_last_arg(t_base *base, t_token *last_token);
void	update_pwd_env(t_base *base, char *new_value);
void	update_for_next_line(t_base *base);
void	update_exit_status(t_base *base, char *exit_nbr);

/* FORMATTING */
int		pipe_redir(t_token *token);
int		format_redirections(t_base *base);
int		manage_in(t_cmd *cmd, char *filepath);
int		manage_out(t_cmd *cmd, char *filepath);
int		manage_append(t_cmd *cmd, char *filepath);

/* EXEC UTILS */
void	close_streams(t_cmd *cmd);
int		get_exit_status(int exit_status);
char	**get_args_tab(t_arg *args, char *path);
char	*ft_triple_strjoin(char const *s1, char const *s2, char const *s3);

/* EXEC UTILS 2 */
void	free_nodes(t_base *base);
t_cmds	*push_commands(t_base *base);
t_cmds	*get_last_cmd(t_cmds *cmds);
void	add_command(t_base *base, t_cmds **cmds, t_cmd *cmd);

/* EXEC */
int		exec_pipes(t_base *base);
int		check_permission(char *path);
int		exec_single_cmd(t_base *base);
int		init_heredoc(t_base *base, t_redir *redir, t_cmd *cmd);

/* EXEC 2 */
void	closing_all_fd(t_base *base);
int		switching_in_out(t_base *base, t_cmd *cmd);

/* BUILTINS */
int		echo(t_base *base, t_cmd *cmd);
int		pwd(t_base *base);
int		is_child_builtin(t_cmd *cmd);
int		is_parent_builtin(t_cmd *cmd);
int		unset(t_base *base, t_cmd *cmd);
int		exec_cd(t_base *base, t_cmd *cmd);
int		print_env(t_base *base, t_cmd *cmd);
void	update_tab_env_export(t_base *base);
int		check_if_exist(t_var *env, char *name);
int		exit_builtin(t_base *base, t_cmd *cmd);
int		builtin_export(t_base *base, t_cmd *cmd);
void	print_export_error(t_base *base, t_arg *arg);
int		exec_child_builtin(t_base *base, t_cmd *cmd);
int		exec_parent_builtin(t_base *base, t_cmd *cmd);
void	add_export(t_base *base, char **array, int equal);

/* LEXER */
char	*ft_findvar_value(t_base *base, char *name);
void	ft_lexer_start(t_base *base, char *line);

/* LEXER UTILS 1 */
int		ft_iswhitespace(char c);
int		ft_isquote(char c);
int		ft_isredirection(char c);
int		ft_isspecial(char c);
int		ft_isspecial_nq(char c);

/* LEXER UTILS 2 */
char	*ft_extract_quotes(t_base *base, char *line, int *i, char quote);
char	*ft_get_developped_vars(t_base *base, char *line);
void	ft_develop_var(t_base *base, char **vars, char *line, int *i);
char	*ft_extract_var_name(char *line, int *i);
int		ft_nb_vars_in_quotes(char *line);

/* LEXER UTILS 3 */
char	*ft_make_quoted_line(t_base *base, char **vars, char *line, int nvars);
char	*ft_join_var_value(char *line, int start, int len, char **vars);
char	*ft_start_quoted_line(char **vars, char *line, int nb_vars, int *i);
char	*ft_get_my_damn_quotes(t_base *base, char *line);
char	*ft_extract_to_quote(t_base *base, char *line, int *index);

/* TOKENS */
void	ft_tokenize(t_base *base, char *value, int id);
void	ft_tokenize_cmd(t_base *base, char *cmd);
void	ft_add_cmd_arg(t_base *base, char *arg);
void	ft_tokenize_redir(t_base *base, char *redir);
void	ft_add_redir_file(t_base *base, char *file);

/* TOKENS LIST UTILS 1 */
t_token	*ft_last_token(t_token *first_token);
t_token	*ft_new_token_node(int id);
void	ft_add_token_node(t_base *base, t_token *new_token);

/* TOKENS UTILS 1 */
int		ft_isbuiltin(char *cmd);
int		ft_isbin(t_base *base, char *cmd);
char	*ft_get_cmdpath(t_base *base, char *cmd, int cmd_id);
int		ft_get_redir(char *redir);

/* CMD LIST UTILS 1 */
t_cmd	*ft_new_cmd_node(int id, char *path, char *name);

/* ARGS LIST UTILS 1 */
t_arg	*ft_last_arg(t_arg *first_arg);
t_arg	*ft_new_arg_node(int id, char *name);
void	ft_add_arg_node(t_cmd *cmd, t_arg *new_arg);

/* REDIR LIST UTILS 1 */
t_redir	*ft_new_redir_node(int id, char *name);

/* VARIABLES UTILS 1 */
char	*ft_get_var_name(t_base *base, char *var);
char	*ft_get_var_value(t_base *base, char *var);
void	ft_add_var(t_base *base, char *input);
void	ft_get_env_vars(t_base *base, char **env);

/* VARIABLES UTILS 2 */
int		type_printable(char *name, int type);
t_var	*ft_findvar(t_var *first_var, char *name);
char	*ft_findvar_value(t_base *base, char *name);

/* VARIABLES LIST UTILS 1 */
t_var	*ft_last_var(t_var *first_var);
void	ft_add_var_node(t_base *base, t_var *new_var);
t_var	*ft_new_var_node(char *name, char *value, int type, int standalone);

#endif