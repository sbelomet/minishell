/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:23 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 14:23:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	ft_del_var_node(t_var *del_var)
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
}*/

static void	ft_del_var_node(t_var **del_var)
{
	t_var	*to_del;

	to_del = *del_var;
	*del_var = (*del_var)->next;
	if ((*del_var)->prev && !(*del_var)->next)
	{
		*del_var = (*del_var)->prev;
		(*del_var)->next = NULL;
	}
	else if ((*del_var)->next && !(*del_var)->prev)
	{
		*del_var = (*del_var)->next;
		(*del_var)->prev = NULL;
	}
	else
	{
		*del_var = (*del_var)->next;
		(*del_var)->prev = to_del->prev;
	}
	free(to_del->name);
	if (to_del->value)
		free(to_del->value);
	free(to_del);
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
			ft_del_var_node(&var);
		var_name = var_name->next;
	}
	return (0);
}
