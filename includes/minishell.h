/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/02 14:48:48 by sbelomet         ###   ########.fr       */
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
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "../libs/ft_printf/libft/libft.h"
# include "../libs/ft_printf/include/ft_printf.h"

# define WHITE "\033[0;39m"
# define B_WHITE "\033[1;39m"

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
	int				fd_in;
	int				fd_out;
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

/* If token is a command and take args/flags !Provisoire! */
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

typedef struct s_base
{
	char			**env;
	t_alloc			*alloc;
	char			*curdir;
	int				after_cmd;
	int				after_redir;
	t_var			*first_var;
	t_token			*first_token;
	int				exit_status;
}					t_base;

/* PROMPT */
void	ft_prompt(t_base *base);

/* ERROR */
void	ft_free(t_base base);
int		errors_lexer(t_base *base);
int		check_err_token_cmd(t_token *token);
void	ft_error(t_base *base, char *message);
int		check_err_token_redirec(t_token *token);

/* FREEING TOKENS */
void	ft_free_tokens(t_token *first_token);

/* BASE INIT */
void	ft_base_init(t_base *base, char **env);
void	ft_get_curdir(t_base *base);

/* SIGNALS UTILS */
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

/* CHECKERS */
int		is_cmd_bin(t_cmd *cmd);
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
int		format_command(t_base *base);
int		format_builtins(t_base *base);

/* BUILTINS */
int		pwd(void); /* PWD */
int		echo(t_cmd *cmd); /* ECHO */
int		print_env(t_var *env_list); /* ENV */
int		exit_builtin(t_cmd *cmd, t_base *base); /* EXIT */

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

/* TOKENS */
void	ft_tokenize(t_base *base, char *value, int id);

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
char	*ft_get_var_name(char *var);
char	*ft_get_var_value(char *var);
void	ft_add_var(t_base *base, char *input);
void	ft_get_env_vars(t_base *base, char **env);

/* VARIABLES UTILS 2 */
t_var	*ft_findvar(t_var *first_var, char *name);
char	*ft_findvar_value(t_base *base, char *name);

/* VARIABLES LIST UTILS 1 */
t_var	*ft_last_var(t_var *first_var);
t_var	*ft_new_var_node(char *name, char *value);
void	ft_add_var_node(t_base *base, t_var *new_var);

#endif