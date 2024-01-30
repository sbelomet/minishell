/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:58:43 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/30 14:52:14 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*ft_findvar_value(t_base *base, char *name)
{
	t_var	*tmp;

	tmp = ft_findvar(base->first_var, ++name);
	if (tmp)
		return (tmp->value);
	return ("");
}

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

char	*ft_extract_sep(char *line, int *index)
{
	int		start;
	int		len;
	char	*res;

	start = *index;
	len = 0;
	while (line[*index] && ft_isseparator(line[*index]))
	{
		(*index)++;
		len++;
	}
	res = ft_substr(line, start, len);
	if (!res)
		return (NULL);
	return (res);
}

void	ft_lexer_start(t_base *base, char *line)
{
	int		i;
	char	*token;
	int		after_cmd;
	int		after_redir;

	i = 0;
	after_cmd = 0;
	after_redir = 0;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
		{
			token = ft_extract_word(base, line, &i);
			if (!token)
				ft_error(base, "malloc()");
			if (!after_cmd && !after_redir)
			{
				ft_tokenize(base, token, TOKEN_CMD);
				after_cmd = 1;
			}
			else if (!after_cmd && after_redir)
			{
				ft_tokenize(base, token, TOKEN_FILE);
				after_redir = 0;
			}
			else if (after_cmd && !after_redir)
				ft_tokenize(base, token, TOKEN_ARG);
			free(token);
		}
		else if (ft_isseparator(line[i]))
		{
			token = ft_extract_sep(line, &i);
			if (!token)
				ft_error(base, "malloc()");
			if (*token == '<' || *token == '>')
				after_redir = 1;
			after_cmd = 0;
			ft_tokenize(base, token, TOKEN_SEP);
			free(token);
		}
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
	}
}
