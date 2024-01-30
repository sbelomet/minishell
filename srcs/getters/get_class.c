/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_class.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:29:18 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 14:14:49 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_token_class(t_token *token)
{
	if (is_token_cmd(token))
		return ((t_cmd *)token->class);
	if (is_token_unknown(token))
		return (NULL /* (t_unknown *)token->class */);
	/* make same for redirec, file and word */
}