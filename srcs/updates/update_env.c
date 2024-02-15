/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:32:09 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 10:47:05 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_tab_env(t_base *base, char *value)
{
	int	i;

	i = -1;
	while (base->env[++i])
	{
		if (ft_strnstr(base->env[i], "PWD", 3))
		{
			free(base->env[i]);
			base->env[i] = ft_strjoin("PWD=", value);
		}
		else if (ft_strnstr(base->env[i], "OLDPWD", 6))
		{
			free(base->env[i]);
			base->env[i] = ft_strjoin("OLDPWD=", value);
		}
	}
}

static void	update_linked_env(t_base *base, char *value)
{
	t_var	*cur_dir;
	t_var	*old_dir;

	cur_dir = ft_findvar(base->first_var, "PWD");
	old_dir = ft_findvar(base->first_var, "OLDPWD");
	if (cur_dir != NULL)
	{
		free(cur_dir->value);
		cur_dir->value = ft_strdup(value);
	}
	if (old_dir != NULL)
	{
		free(old_dir->value);
		old_dir->value = ft_strdup(base->curdir);
	}
}

void	update_pwd_env(t_base *base, char *new_value)
{
	update_tab_env(base, new_value);
	update_linked_env(base, new_value);
	free(base->curdir);
	base->curdir = ft_strdup(new_value);
}
