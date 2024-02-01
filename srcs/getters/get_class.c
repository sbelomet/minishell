/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_class.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:29:18 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 10:55:27 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_token_class(t_token *token)
{
	if (is_token_cmd(token))
		return ((t_cmd *)token->type);
	if (is_token_unknown(token))
		return ((t_unknown *)token->type);
	if (is_token_file(token))
		return ((t_file *)token->type);
	if (is_token_redirec(token))
		return ((t_redir *)token->type);
}