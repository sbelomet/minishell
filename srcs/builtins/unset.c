/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:23 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/01 11:01:46 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del_var_node(t_var *del_var)
{
	t_var	*prev_var;
	t_var	*next_var;

	if (del_var)
	{
		prev_var = del_var->prev;
		next_var = del_var->next;
		if (prev_var)
			prev_var->next = next_var;
		if (next_var)
			next_var->prev = prev_var;
		if (del_var->name)
			free(del_var->name);
		if (del_var->value)
			free(del_var->value);
		free(del_var);
	}	
}

int	unset(t_base *base, t_cmd *cmd)
{
	t_arg	*var_name;
	t_var	*var;

	var_name = cmd->first_arg;
	while (var_name)
	{
		var = ft_findvar(base->first_var, var_name->name);
		if (var)
			ft_del_var_node(var);
		var_name = var_name->next;
	}
	return (0);
}
