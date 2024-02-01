/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:59:24 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/01 15:05:51 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_new_redir_node(int id, char *name)
{
	t_redir	*res;

	res = (t_redir *)malloc(sizeof(t_redir));
	if (!res)
		return (NULL);
	res->id = id;
	res->name = name;
	res->fd_in = -1;
	res->fd_out = -1;
	res->file = NULL;
	return (res);
}
