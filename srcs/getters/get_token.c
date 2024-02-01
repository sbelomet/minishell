/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:54:35 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 11:51:17 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_first_token(t_base *base)
{
	if (base->first_token)
		return (base->first_token);
	return (0);
}

t_token	*get_first_cmd(t_base *base)
{
    t_token *token;

    token = get_first_token(base);
    while (token)
    {
        if (is_token_cmd(token))
            return (get_token_class(token));
        token = token->next;
    }
    return (NULL);
}

t_token	*get_first_builtin(t_base *base)
{
    t_token *token;

    token = get_first_token(base);
    while (token)
    {
        if (is_token_builtin(token))
            return (get_token_class(token));
        token = token->next;
    }
    return (NULL);
}