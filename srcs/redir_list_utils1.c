/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:59:24 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/02 14:13:32 by sbelomet         ###   ########.fr       */
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
	res->fd_in = STDIN_FILENO;
	res->fd_out = STDOUT_FILENO;
	res->file_fd = -1;
	res->limiter = NULL;
	res->filepath = NULL;
	return (res);
}
