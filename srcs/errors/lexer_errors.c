/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 10:24:21 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errors_lexer(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_redirec(token) && check_err_token_redirec(token) == 0)
			return (1);
		if (is_token_cmd(token))
		{
			cmd = get_token_class(token);
			if (cmd->id == TOKEN_BIN && !cmd->path)
			{
				ft_printf(1, "command not found: %s\n", cmd->name);
				base->exit_status = 127;
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
