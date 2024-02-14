/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:18:57 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:09:56 by sbelomet         ###   ########.fr       */
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

int	check_err_token_redirec(t_token *token)
{
	t_redir	*redir;

	redir = get_token_class(token);
	if (is_token_heredoc(token)
		&& (!redir->limiter || limiter_check(redir->limiter)))
	{
		ft_printf(2, "syntax error near unexpected token `%s'", redir->limiter);
		return (0);
	}
	if (is_token_redirec(token))
	{
		if (!redir->filepath) // if no file, what is the filepath? ex. cat < | rev > out ('|' is now in the filepath?)
		{
			// message printf 
			return (0);
		}
		if (!redir->filepath && !token->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'", 2);
			return (0);
		}
	}
	return (1);
}
