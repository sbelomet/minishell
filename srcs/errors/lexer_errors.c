/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 10:04:42 by sbelomet         ###   ########.fr       */
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
		if (is_token_redirec(token) && !check_err_token_redirec(token))
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
