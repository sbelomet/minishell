/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:33:45 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/01 13:16:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_last_arg(t_arg *first_arg)
{
	t_arg	*tmp;

	tmp = first_arg;
	if (tmp)
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
	}
	return (tmp);
}

t_arg	*ft_new_arg_node(int id, char *name)
{
	t_arg	*res;

	res = (t_arg *)malloc(sizeof(t_arg));
	if (!res)
		return (NULL);
	res->id = id;
	res->name = name;
	res->index = 0;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void	ft_add_arg_node(t_cmd *cmd, t_arg *new_arg)
{
	t_arg	*last;

	if (cmd->first_arg)
	{
		last = ft_last_arg(cmd->first_arg);
		last->next = new_arg;
		new_arg->prev = last;
		new_arg->index++;
	}
	else
		cmd->first_arg = new_arg;
}
