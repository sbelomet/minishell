/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:58:43 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/26 15:43:45 by sbelomet         ###   ########.fr       */
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

int	ft_isseparator(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' || c == '=')
		return (1);
	return (0);
}

int	ft_isspecial(char c)
{
	if (c == '$' || ft_isseparator(c) || ft_isquote(c)
		|| ft_iswhitespace(c))
		return (1);
	return (0);
}

void	ft_lexer_start(t_base *base, char *line)
{
	int		i;
	int		len;
	int		start;
	char	*token;

	i = 0;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
		{
			start = i;
			len = 0;
			while (line[i] && !ft_isspecial(line[i]))
			{
				i++;
				len++;
			}
			token = ft_substr(line, start, len);
			if (!token)
				ft_error(base, "malloc()");
			ft_tokenize(base, token, 0);
			free(token);
		}
		else if (ft_isseparator(line[i]))
		{
			start = i;
			len = 0;
			while (line[i] && ft_isseparator(line[i]))
			{
				i++;
				len++;
			}
			token = ft_substr(line, start, len);
			if (!token)
				ft_error(base, "malloc()");
			ft_tokenize(base, token, 1);
			free(token);
		}
		else if (line[i] == '$')
		{
			i++;
			start = i;
			len = 0;
			while (line[i] && ft_isalnum(line[i]))
			{
				i++;
				len++;
			}
			token = ft_substr(line, start, len);
			if (!token)
				ft_error(base, "malloc()");
			ft_tokenize(base, token, 2);
			free(token);
		}
		while (line[i] && ft_iswhitespace(line[i]))
		{
			i++;
		}
	}
}
