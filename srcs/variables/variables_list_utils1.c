/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_list_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:16:14 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/27 10:38:08 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_last_var(t_var *first_var)
{
	t_var	*tmp;

	tmp = first_var;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_var	*ft_new_var_node(char *name, char *value,
	int type, int standalone)
{
	t_var	*res;

	res = (t_var *)malloc(sizeof(t_var));
	if (!res)
		return (NULL);
	res->name = name;
	if (!value)
		res->value = ft_strdup("");
	else
		res->value = value;
	res->standalone = standalone;
	res->printable = type_printable(name, type);
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void	ft_add_var_node(t_base *base, t_var *new_var)
{
	t_var	*last;

	if (base->first_var)
	{
		last = ft_last_var(base->first_var);
		last->next = new_var;
		new_var->prev = last;
	}
	else
		base->first_var = new_var;
}
