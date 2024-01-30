/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/30 15:43:18 by lgosselk         ###   ########.fr       */
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

# define TOKEN_CMD 0
# define TOKEN_BUILTIN 1
# define TOKEN_BIN 2
# define TOKEN_SEP 3
# define TOKEN_PIPE 4
# define TOKEN_REDIR 5
# define TOKEN_FILE 6
# define TOKEN_ARG 7

typedef struct s_token
{
	void			*type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_file
{
	char			*path;
	int				fd;
}					t_file;

typedef struct s_sep
{
	char			*name;
	int				type;
}					t_sep;

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
	char			*value;
}					t_arg;

/* If token is a command and take args/flags !Provisoire! */
typedef struct s_cmd
{
	int				id;
	int				pid;
	char			*arg;
	char			*bin;
	int				fd_in;
	char			*flags;
	char			**args;
	int				fd_out;
	char			*content;
	t_arg			*first_arg;
}					t_cmd;

typedef struct s_base
{
	char			**env;
	t_alloc			*alloc;
	char			*curdir;
	t_var			*first_var;
	t_token			*first_token;
	int				exit_status;
	t_token			*first_token;
}				t_base;

/* PROMPT */
void	ft_prompt(t_base *base);

/* VARIABLES UTILS 1 */
char	*ft_get_var_name(char *var);
char	*ft_get_var_value(char *var);
void	ft_add_var(t_base *base, char *input);
void	ft_get_env_vars(t_base *base, char **env);
t_var	*ft_findvar(t_var *first_var, char *name);

/* VARIABLES UTILS 2 */
t_var	*ft_last_var(t_var *first_var);
t_var	*ft_new_var_node(char *name, char *value);
void	ft_add_var_node(t_base *base, t_var *new_var);

/* ERROR */
void	ft_free(t_base base);
int		errors_lexer(t_base *base);
int		check_err_token_cmd(t_token *token);
void	ft_error(t_base *base, char *message);
int 	check_err_token_redirec(t_token *token);

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
t_token	*get_first_token(t_base *base);
void	*get_token_class(t_token *token);

/* CHECKERS */
int		is_cmd_bin(t_cmd *cmd);
int		is_cd_builtin(t_cmd *cmd);
int		is_pwd_builtin(t_cmd *cmd);
int		is_cmd_builtin(t_cmd *cmd);
int		is_env_builtin(t_cmd *cmd);
int		is_echo_builtin(t_cmd *cmd);
int		is_token_cmd(t_token *token);
int		is_token_bin(t_token *token);
int		is_token_pipe(t_token *token);
int		is_export_builtin(t_cmd *cmd);
int		is_token_file(t_token *token);
int		is_token_redirec(t_token *token);
int		is_token_heredoc(t_token *token);
int		is_token_unknown(t_token *token);
int		is_token_input_redirec(t_token *token);
int		is_token_append_redirec(t_token *token);

/* BUILTINS */
int		pwd(void); /* PWD */
int		echo(t_cmd *cmd); /* ECHO */
int		print_env(t_var *env_list); /* ENV */
int		exit_builtin(t_cmd *cmd, t_base *base); /* EXIT */

/* LEXER */
void	ft_lexer_start(t_base *base, char *line);

/* LEXER UTILS1 */
int		ft_iswhitespace(char c);
int		ft_isquote(char c);
int		ft_isseparator(char c);
int		ft_isspecial(char c);

/* TOKENS */
void	ft_tokenize(t_base *base, char *value, int type);

/* TOKENS UTILS 1 */
t_token	*ft_last_token(t_token *first_token);
t_token	*ft_new_token_node(void);
void	ft_add_token_node(t_base *base, t_token *new_token);

#endif