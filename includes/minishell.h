/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/23 15:02:02 by sbelomet         ###   ########.fr       */
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

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*prev;
	struct s_var	*next;
}					t_var;

typedef struct s_base
{
	char	**env;
	t_var	*first_var;
}			t_base;

/* UTILS */
void	ft_free(t_base base);

/* VARIABLES UTILS*/
t_var	*ft_last_var(t_var *first_var);
t_var	*ft_new_var_node(char *name, char *value);
void	ft_add_var_node(t_base *base, t_var *new);
char	*ft_get_var_value(char *var);
char	*ft_get_var_name(char *var);
void	ft_get_env_vars(t_base *base, char **env);
void	ft_add_var(t_base *base, char *input);

/* ERROR UTILS */
void	ft_error(t_base *base, char *message);

#endif