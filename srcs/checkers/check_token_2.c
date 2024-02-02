/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:19:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/01 15:02:20 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_token_unknown(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_UNKNOWN)
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
	if (token->id == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_token_basic_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == TOKEN_APPENDREDIR || token->id == TOKEN_OUTREDIR
		|| token->id == TOKEN_INREDIR)
		return (1);
	return (0);
}
