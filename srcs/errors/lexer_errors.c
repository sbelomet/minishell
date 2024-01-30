/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:24:49 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 14:20:17 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	errors_lexer(t_base *base)
{
	t_token	*token;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_cmd(token) && check_err_token_cmd(token))
			return (1);
		if (is_token_redirec(token) && check_err_token_redirec(token))
			return (1);
		if (is_token_unknown(token))
		{
			// get_class_token
			// ft_printf content;
			// update env status to 127  
		}
		token = token->next;
	}
}