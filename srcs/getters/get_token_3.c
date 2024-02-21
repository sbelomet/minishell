/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:29:57 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:19:04 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_first_token_cmd(t_base *base)
{
	t_token	*token;

	if (base->first_token)
	{
		token = base->first_token;
		while (token)
		{
			if (is_token_cmd(token))
				return (token);
			token = token->next;
		}
	}
	return (NULL);
}

t_token	*get_first_token_cmd_no_skip(t_base *base)
{
	t_token	*token;

	if (base->first_token)
	{
		token = base->first_token;
		while (token)
		{
			if (is_token_pipe(token))
				return (NULL);
			else if (is_token_cmd(token))
				return (token);
			token = token->next;
		}
	}
	return (NULL);
}
