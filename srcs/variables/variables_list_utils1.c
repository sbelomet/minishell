/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_list_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:16:14 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/20 15:38:11 by sbelomet         ###   ########.fr       */
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

t_var	*ft_new_var_node(char *name, char *value)
{
	t_var	*res;

	res = (t_var *)malloc(sizeof(t_var));
	if (!res)
		return (NULL);
	res->name = name;
	res->value = value;
	res->printable = 1;
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

void	ft_del_var_node(t_var *del_var)
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
