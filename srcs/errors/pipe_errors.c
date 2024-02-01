/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:15:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 11:02:01 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_err_token_pipe(t_token *token)
{
	t_redir	*redir;

	redir = get_token_class(token);
	if (is_token_pipe(token))
	{
		if (!is_token_cmd(token->next) || !token->next)
		{
			ft_printf("Error: command after pipe [%s] not found", NULL /* redir->name */);
			return (1);
		}
		else if (!is_token_cmd(token->prev) || !token->prev)
		{
			ft_printf("Error: command before pipe [%s] not found", NULL /* redir->name */);
			return (1);
		}
		return (0);
	}
	return (1);
}