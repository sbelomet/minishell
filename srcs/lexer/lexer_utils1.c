/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:07:38 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/02 14:05:39 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_isredirection(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|')
		return (1);
	return (0);
}

int	ft_isspecial(char c)
{
	if (ft_isredirection(c) || ft_isquote(c) || ft_iswhitespace(c))
		return (1);
	return (0);
}
