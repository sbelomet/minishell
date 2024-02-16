/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:19:13 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 11:46:50 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_cmd(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_BIN || token->id == TOKEN_BUILTIN)
		return (1);
	return (0);
}

int	is_token_bin(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_BIN)
		return (1);
	return (0);
}

int	is_token_builtin(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_BUILTIN)
		return (1);
	return (0);
}

int	is_token_redirec(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_REDIR || token->id == TOKEN_REDIR_APP
		|| token->id == TOKEN_REDIR_HDOC || token->id == TOKEN_REDIR_IN
		|| token->id == TOKEN_REDIR_OUT)
		return (1);
	return (0);
}

int	is_token_pipe(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_PIPE)
		return (1);
	return (0);
}
