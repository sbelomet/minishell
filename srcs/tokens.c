/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:16:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/31 14:35:21 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize(t_base *base, char *val, int id)
{
	t_token	*res;
	char	*path;

	res = ft_new_token_node(id);
	if (!res)
		ft_error(base, "malloc()");
	ft_add_token_node(base, res);
	path = NULL;
	if (id == TOKEN_CMD)
	{
		if (ft_isbuiltin(base, val))
			res->id = TOKEN_BUILTIN;
		else if (ft_isbin(base, val))
		{
			res->id = TOKEN_BIN;
			path = ft_get_cmdpath(base, val);
		}
		else
			res->id = TOKEN_UNKNOWN;
		res->type = ft_new_cmd_node(res->id, path, val);
		free(path);
	}

	t_cmd *test;

	test = (t_cmd *)res->type;
	printf("name: %s, id: %d, path: %s\n", test->name, test->id, test->path);
}
