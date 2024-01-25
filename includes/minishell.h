/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/25 11:54:17 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/ft_printf/include/ft_printf.h"
# include "../libs/ft_printf/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

# define WHITE "\033[0;39m"
# define B_WHITE "\033[1;39m"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*prev;
	struct s_var	*next;
}					t_var;

typedef struct s_base
{
	char	*curdir;
	char	**env;
	t_var	*first_var;
}			t_base;

/* PROMPT */
void	ft_prompt(t_base *base);

/* VARIABLES UTILS*/
t_var	*ft_last_var(t_var *first_var);
t_var	*ft_new_var_node(char *name, char *value);
void	ft_add_var_node(t_base *base, t_var *new_var);
char	*ft_get_var_value(char *var);
char	*ft_get_var_name(char *var);
void	ft_get_env_vars(t_base *base, char **env);
void	ft_add_var(t_base *base, char *input);

/* ERROR UTILS */
void	ft_error(t_base *base, char *message);
void	ft_free(t_base base);

/* BASE INIT */
void	ft_base_init(t_base *base, char **env);
void	ft_get_curdir(t_base *base);

/* SIGNALS UTILS */
void	ft_ctrl_slash(int signum);
void	ft_ctrl_c(int signum);

#endif