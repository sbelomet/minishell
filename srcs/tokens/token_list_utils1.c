/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:09 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/21 12:14:42 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_last_token(t_token *first_token)
{
	t_token	*tmp;

	tmp = first_token;
	if (tmp)
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
	}
	return (tmp);
}

t_token	*ft_new_token_node(int id)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->type = NULL;
	res->id = id;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void	ft_add_token_node(t_base *base, t_token *new_token)
{
	t_token	*last;

	if (base->first_token)
	{
		last = ft_last_token(base->first_token);
		last->next = new_token;
		new_token->prev = last;
	}
	else
		base->first_token = new_token;
}
