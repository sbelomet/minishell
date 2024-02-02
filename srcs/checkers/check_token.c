/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:19:13 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/01 15:17:20 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (token->id == TOKEN_REDIR || token->id == TOKEN_OUTREDIR
        || token->id == TOKEN_INREDIR || token->id == TOKEN_APPENDREDIR)
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
