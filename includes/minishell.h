/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/09 15:50:38 by sbelomet         ###   ########.fr       */
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

# include "../libs/ft_printf/libft/libft.h"
# include "../libs/ft_printf/include/ft_printf.h"

# define WHITE "\033[0;39m"
# define B_WHITE "\033[1;39m"
# define TMP_FILE "/tmp/minishell.tmp"

enum e_types
{
	TOKEN_UNKNOWN_CMD,
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

typedef struct s_unknown
{
	int				id;
	char			*name;
}					t_unknown;

typedef struct s_var
{
	char			*name;
	char			*value;
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
	int				pid;
	char			*path;
	int				fd_in;
	int				fd_out;
	char			*name;
	t_arg			*first_arg;
}					t_cmd;

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
	t_lexvars		lexvars; // A BANNIR!! // LAISSE MA STRUCT TRANQUILLE
	int				pipe;
	int				exit_status;
	int				pipe;
}					t_base;

int		g_error;

/* PROMPT */
void	ft_prompt(t_base *base);

/* ERROR */
void	ft_free(t_base base);
int		errors_lexer(t_base *base);
int		check_err_token_pipe(t_token *token);
void	ft_error(t_base *base, char *message);
int		check_err_token_redirec(t_token *token);
int		check_err_token_pipe(t_token *token);

/* FREEING TOKENS */
void	ft_free_tokens(t_token *first_token);

/* BASE INIT */
void	ft_base_init(t_base *base, char **env);
void	ft_get_curdir(t_base *base);

/* SIGNALS UTILS */
void	ft_signals(void);
void	ft_ctrl_slash(int signum);
void	ft_ctrl_c(int signum);

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
t_token	*get_next_token_cmd(t_token *token);
t_cmd	*get_prev_cmd_no_skip(t_token *token);
t_cmd	*get_next_cmd_no_skip(t_token *token);

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
int		is_token_unknown(t_token *token);
int		is_token_builtin(t_token *token);
int		is_token_basic_redir(t_token *token);
int		is_builtin_cmd(char *name, t_cmd *cmd);

/* UPDATES */
int		update_env(t_base *base, char *name, char *new_value);

/* FORMATTING */
int		format_builtins(t_base *base);
int		format_redirections(t_base *base);

/* FILE UTILS */
int		open_file(char *path, int type);

/* EXEC UTILS */
void	close_streams(t_cmd *cmd);
char	**get_args_tab(t_arg *args);
int		get_exit_status(int exit_status);
void	dup_redir(t_token *token, int *fds, int in_fd);
char	*ft_triple_strjoin(char const *s1, char const *s2, char const *s3);

/* EXEC */
int		exec_pipes(t_base *base);
int		exec_single_cmd(t_base *base);
int		init_heredoc(t_base *base, t_redir *redir, t_cmd *cmd);

/* BUILTINS */
int		pwd(void);
int		echo(t_cmd *cmd);
int		print_env(t_var *env_list);
int		unset(t_base *base, t_cmd *cmd);
int		is_child_builtin(t_cmd *cmd);
int		is_parent_builtin(t_cmd *cmd);
int		exit_builtin(t_cmd *cmd, t_base *base);
int		exec_child_builtin(t_base *base, t_cmd *cmd);
int		exec_parent_builtin(t_base *base, t_cmd *cmd);

/* READ LINE */
void	exec_line(t_base *base, char *line);

/* LEXER */
char	*ft_findvar_value(t_base *base, char *name);
void	ft_lexer_start(t_base *base, char *line);

/* LEXER UTILS 1 */
int		ft_iswhitespace(char c);
int		ft_isquote(char c);
int		ft_isredirection(char c);
int		ft_isspecial(char c);

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
char	*ft_get_cmdpath(t_base *base, char *cmd);
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
t_var	*ft_findvar(t_var *first_var, char *name);
char	*ft_findvar_value(t_base *base, char *name);

/* VARIABLES LIST UTILS 1 */
t_var	*ft_last_var(t_var *first_var);
t_var	*ft_new_var_node(char *name, char *value);
void	ft_add_var_node(t_base *base, t_var *new_var);
void	ft_del_var_node(t_base *base, t_var *del_var);

#endif