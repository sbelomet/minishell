/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:18:57 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 16:01:43 by lgosselk         ###   ########.fr       */
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
        printf("CHECK ERROR\n");
		if (!redir->filepath && redir->id != TOKEN_REDIR_HDOC)
		{
            printf("id: %d\n", redir->id);
            printf("CHECK ERROR NO PATH\n");
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
