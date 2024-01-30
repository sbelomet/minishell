/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:24:02 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 14:46:27 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_err_token_cmd(t_token *token)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;

	cmd = get_token_class(token);
	if (is_token_cmd(token->next))
	{
		next_cmd = get_token_class(token->next);
		ft_printf("Error : Two following commands [%s and %s]\n",
			cmd->content, next_cmd->content);
		return (1);
	}
	else if (is_token_cmd(token->prev))
	{
		prev_cmd = get_token_class(token->prev);
		ft_printf("Error : Two following commands [%s and %s]\n",
			prev_cmd->content, cmd->content);
		return (1);
	}
	return (0);
}