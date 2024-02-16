/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 14:22:01 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errors_lexer(t_base *base)
{
	t_token		*token;
	//t_unknown	*unknown;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_redirec(token) && !check_err_token_redirec(token))
			return (1);
		//if (is_token_unknown(token))
		//{
		//	unknown = get_token_class(token);
		//	if (unknown->id == TOKEN_UNKNOWN_REDIR)
		//		ft_printf(1, "Error: Unknown redirection [%s]\n", unknown->name);
		//	//g_error = 127;
		//}
		token = token->next;
	}
	return (0);
}
