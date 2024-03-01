/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:32:09 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/01 10:25:11 by lgosselk         ###   ########.fr       */
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
			base->env[i] = ft_strjoin_alloc("PWD=", value, &base->alloc);
		else if (ft_strnstr(base->env[i], "OLDPWD", 6))
			base->env[i] = ft_strjoin_alloc("OLDPWD=", value, &base->alloc);
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

void	update_exit_status(t_base *base, char *exit_nbr)
{
	t_var	*exit_status;

	exit_status = ft_findvar(base->first_var, "?");
	if (exit_status != NULL)
	{
		free(exit_status->value);
		if (!exit_nbr)
			exit_status->value = ft_itoa(base->exit_status);
		else
			exit_status->value = ft_strdup(exit_nbr);
	}
}

void	update_pwd_env(t_base *base, char *new_value)
{
	update_tab_env(base, new_value);
	update_linked_env(base, new_value);
	free(base->curdir);
	base->curdir = ft_strdup(new_value);
}
