/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:18:57 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 11:30:46 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_err_token_redirec(t_token *token)
{
    t_redir	*redir;

	redir = get_token_class(token);
	if (is_token_heredoc(token) /* && !redir->limiter */)
	{
		ft_printf("Error: limiter not found for heredoc [%s]\n", NULL /* redir->name */);
		return (1);
	}
	if (is_token_redirec(token))
	{
		if (!token->next || !is_token_file(token->next))
		{
			ft_printf("Error: file not found for redirection [%s]\n", NULL /* redir->name */);
			return (1);
		}
	}
	return (0);
}