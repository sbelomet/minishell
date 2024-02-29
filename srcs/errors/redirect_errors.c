/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:18:57 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:35:50 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	limiter_check(char *limiter)
{
	while (*limiter)
	{
		if ((*limiter == '|' || *limiter == '<' || *limiter == '>'))
			return (1);
		limiter++;
	}
	return (0);
}

static int	print_unknown(t_redir *redir)
{
	ft_printf(2, "syntax error near unexpected token `%s'\n", redir->filepath);
	return (0);
}

int	check_err_token_redirec(t_token *token)
{
	t_redir	*redir;

	redir = get_token_class(token);
	if (is_token_redirec(token))
	{
		if (redir->id == TOKEN_UNKNOWN_REDIR)
			return (print_unknown(redir));
		if (is_token_heredoc(token)
			&& (!redir->limiter || limiter_check(redir->limiter)))
		{
			ft_printf(2, "syntax error near unexpected token `%s'\n",
				redir->limiter);
			return (0);
		}
		if (!redir->filepath && !token->next && !is_token_heredoc(token))
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (0);
		}
	}
	return (1);
}
