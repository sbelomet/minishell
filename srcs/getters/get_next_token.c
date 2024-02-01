/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:17 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 16:06:15 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *get_next_builtin(t_token *token)
{
	token = token->next;
	while (token)
	{
		if (is_token_builtin(token))
			return (token);
		token = token->next;
	}
	return (NULL);
}