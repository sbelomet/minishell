/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:15:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:09:49 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_err_token_pipe(t_token *token)
{
	t_redir	*redir;

	redir = get_token_class(token);
	if (is_token_pipe(token))
	{
		if (token->prev == NULL || is_token_redirec(token->prev))
		{
			ft_putstr_fd("syntax error near unexpected token `|'", 2);
			return (0);
		}
	}
	return (1);
}
