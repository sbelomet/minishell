/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:19:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:09:17 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_unknown(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_UNKNOWN_CMD
		|| token->id == TOKEN_UNKNOWN_REDIR)
		return (1);
	return (0);
}

int	is_token_file(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_FILE)
		return (1);
	return (0);
}

int	is_token_heredoc(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_REDIR_HDOC)
		return (1);
	return (0);
}

int	is_token_basic_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_REDIR_APP || token->id == TOKEN_REDIR_OUT
		|| token->id == TOKEN_REDIR_IN)
		return (1);
	return (0);
}
