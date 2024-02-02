/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/01 15:46:09 by lgosselk         ###   ########.fr       */
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
			ft_printf("Error: Unknown token [%s]\n", unknown->name);
			if (update_env(base, "?", ft_itoa(127)))
				return (1);
		}
        // check token_unknown redir, cmd
		token = token->next;
	}
	return (0);
}