/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:19:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 13:37:16 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_token_input_redirec(t_token *token)
{
	if (!token)
		return (0);
	if (token->id /* // equal to TOKEN_INPUT_REDIREC */)
		return (1);
	return (0);
}

int	is_token_append_redirec(t_token *token)
{
	if (!token)
		return (0);
	if (token->id /* // equal to TOKEN_APPEND_REDIREC */)
		return (1);
	return (0);
}

int	is_token_unknown(t_token *token)
{
	if (!token)
		return (0);
	if (token->id /* // equal to TOKEN_UNKNOWN */)
		return (1);
	return (0);
}

int	is_token_file(t_token *token)
{
	if (!token)
		return (0);
	if (token->id /* // equal to TOKEN_FILE */)
		return (1);
	return (0);
}

// is_token_basic_redirection and _is redir_heredoc necessary?