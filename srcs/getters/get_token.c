/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:54:35 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:19:17 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_first_token(t_base *base)
{
	if (base->first_token)
		return (base->first_token);
	return (0);
}

t_token	*get_first_cmd(t_base *base)
{
	t_token	*token;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_cmd(token))
			return (get_token_class(token));
		token = token->next;
	}
	return (NULL);
}

t_token	*get_first_builtin(t_base *base)
{
	t_token	*token;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_builtin(token))
			return (get_token_class(token));
		token = token->next;
	}
	return (NULL);
}

t_token	*get_next_token_cmd(t_token *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		token = token->next;
		if (is_token_cmd(token))
			return (token);
	}
	return (NULL);
}
