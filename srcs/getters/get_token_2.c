/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:17 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 16:06:15 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_builtin(t_token *token)
{
	token = token->next;
	while (token)
	{
		if (is_token_builtin(token))
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_cmd	*get_next_cmd(t_token *token)
{
	while (token)
	{
		if (is_token_cmd(token))
			return (get_token_class(token));
		token = token->next;
	}
	return (NULL);
}

t_cmd	*get_prev_cmd(t_token *token)
{
	while (token)
	{
		if (is_token_cmd(token))
			return (get_token_class(token));
		token = token->prev;
	}
	return (NULL);
}

t_cmd	*get_prev_cmd_no_skip(t_token *token)
{
	while (token)
	{
		if (is_token_pipe(token))
			return (NULL);
		if (is_token_cmd(token))
			return (get_token_class(token));
		token = token->prev;
	}
	return (NULL);
}

t_cmd	*get_next_cmd_no_skip(t_token *token)
{
	while (token)
	{
		if (is_token_pipe(token))
			return (NULL);
		if (is_token_cmd(token))
			return (get_token_class(token));
		token = token->next;
	}
	return (NULL);
}
