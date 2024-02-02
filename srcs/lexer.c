/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:58:43 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/02 14:55:21 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_word(t_base *base, char *line, int *index)
{
	int		start;
	int		len;
	char	*res;
	char	*tmp;

	start = *index;
	len = 0;
	while (line[*index] && !ft_isspecial(line[*index]))
	{
		(*index)++;
		len++;
	}
	tmp = ft_substr(line, start, len);
	if (!tmp)
		return (NULL);
	if (*tmp == '$')
	{
		res = ft_findvar_value(base, tmp);
		free(tmp);
		tmp = ft_strdup(res);
		return (tmp);
	}
	return (tmp);
}

char	*ft_extract_redir(char *line, int *index)
{
	int		start;
	int		len;
	char	*res;

	start = *index;
	len = 0;
	while (line[*index] && ft_isredirection(line[*index]))
	{
		(*index)++;
		len++;
	}
	res = ft_substr(line, start, len);
	if (!res)
		return (NULL);
	return (res);
}

void	ft_find_noredir_word(t_base *base, char *line, int *i)
{
	char	*token;

	token = ft_extract_word(base, line, i);
	printf("token: %s\n", token);
	if (!token)
		ft_error(base, "malloc()");
	if (!base->after_cmd && !base->after_redir)
	{
		if (ft_strchr(token, '='))
			ft_tokenize(base, token, TOKEN_VAR);
		else
		{
			ft_tokenize(base, token, TOKEN_CMD);
			base->after_cmd = 1;
		}
	}
	else if (!base->after_cmd && base->after_redir)
	{
		ft_tokenize(base, token, TOKEN_FILE);
		base->after_redir = 0;
	}
	else if (base->after_cmd && !base->after_redir)
		ft_tokenize(base, token, TOKEN_ARG);
}

void	ft_find_redir_word(t_base *base, char *line, int *i)
{
	char	*token;

	token = ft_extract_redir(line, i);
	if (!token)
		ft_error(base, "malloc()");
	if (*token == '<' || *token == '>')
		base->after_redir = 1;
	base->after_cmd = 0;
	ft_tokenize(base, token, TOKEN_REDIR);
}

void	ft_lexer_start(t_base *base, char *line)
{
	int		i;
	char	*in_quotes;

	i = 0;
	base->after_cmd = 0;
	base->after_redir = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]))
		{
			in_quotes = ft_extract_quotes(base, line, &i, line[i]);
		}
		else if (!ft_isspecial(line[i]))
			ft_find_noredir_word(base, line, &i);
		else if (ft_isredirection(line[i]))
			ft_find_redir_word(base, line, &i);
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
	}
}
