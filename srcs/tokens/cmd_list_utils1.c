/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:38:05 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/20 10:27:27 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_new_cmd_node(int id, char *path, char *name)
{
	t_cmd	*res;

	res = (t_cmd *)malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->id = id;
	if (id == TOKEN_WORD)
		res->id = TOKEN_BIN;
	res->pid = -1;
	res->path = path;
	res->name = name;
	res->fd_in = STDIN_FILENO;
	res->fd_out = STDOUT_FILENO;
	res->first_arg = NULL;
	return (res);
}
