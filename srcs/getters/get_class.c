/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_class.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:29:18 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:20:00 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*get_token_class(t_token *token)
{
	if (is_token_cmd(token))
		return ((t_cmd *)token->type);
	if (is_token_redirec(token))
		return ((t_redir *)token->type);
	return (NULL);
}
