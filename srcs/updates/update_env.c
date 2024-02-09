/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:32:09 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 15:27:37 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*get_node(t_var *vars, char*value)
{
	if (!vars)
		return (NULL);
	
}

static void	update_tab_env()
{

}

static void	update_linked_env()
{
	
}

int	update_env(t_base *base, char *name, char *new_value) // update tab env in base and update linked list
{
	t_var	*var;

	if (!new_value)
		return (1);
	var = ft_findvar(base, name);
	if (!var)
		return (1);
	if (var->value)
		free(var->value);
	var->value = new_value;
	return (0);
}