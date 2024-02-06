/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/05 09:52:07 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	errors_lexer(t_base *base)
{
	t_token		*token;
	t_unknown	*unknown;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_cmd(token) && check_err_token_cmd(token))
			return (1);
		if (is_token_redirec(token) && check_err_token_redirec(token))
			return (1);
		if (is_token_pipe(token) && check_err_token_pipe(token))
			return (1);
		if (is_token_unknown(token))
		{
			unknown = get_token_class(token);
			if (unknown->id == TOKEN_UNKNOWN_CMD)
				ft_printf("Error: Unknown command [%s]\n", unknown->name);
			else if (unknown->id == TOKEN_UNKNOWN_REDIR)
				ft_printf("Error: Unknown redirection [%s]\n", unknown->name);
			if (update_env(base, "?", ft_itoa(127)))
				return (1);
		}
		token = token->next;
	}
	return (0);
}