/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:58:43 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/29 10:42:41 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_word(t_base *base, char *line, int *index)
{
	char	*res;
	char	*tmp;
	char	*q_part;

	res = ft_strdup("");
	while (line[*index] && !ft_isspecial_nq(line[*index]))
	{
		tmp = ft_extract_to_quote(base, line, index);
		if (ft_equal_strs(tmp, "~"))
		{
			free(tmp);
			tmp = ft_strdup(ft_findvar_value(base, "$HOME"));
			if (!tmp)
				ft_error(base);
		}
		if (ft_isquote(line[*index]))
		{
			q_part = ft_extract_quotes(base, line, index, line[*index]);
			tmp = ft_strjoin_free(tmp, q_part);
		}
		res = ft_strjoin_free(res, tmp);
	}
	return (res);
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
	char		*token;
	t_lexvars	*lexvars;

	lexvars = &base->lexvars;
	token = ft_extract_word(base, line, i);
	if (!token)
		ft_error(base);
	if (!lexvars->after_cmd && !lexvars->after_redir)
	{
		if (ft_strchr(token, '='))
			ft_tokenize(base, token, TOKEN_VAR);
		else
		{
			ft_tokenize(base, token, TOKEN_CMD);
			lexvars->after_cmd = 1;
		}
	}
	else if (!lexvars->after_cmd && lexvars->after_redir)
	{
		ft_tokenize(base, token, TOKEN_FILE);
		lexvars->after_redir = 0;
	}
	else if (lexvars->after_cmd && !lexvars->after_redir)
		ft_tokenize(base, token, TOKEN_ARG);
}

void	ft_find_redir_word(t_base *base, char *line, int *i)
{
	char	*token;

	token = ft_extract_redir(line, i);
	if (!token)
		ft_error(base);
	if (*token == '<' || *token == '>')
		base->lexvars.after_redir = 1;
	base->lexvars.after_cmd = 0;
	ft_tokenize(base, token, TOKEN_REDIR);
}

void	ft_lexer_start(t_base *base, char *line)
{
	int		i;

	i = 0;
	base->lexvars = (t_lexvars){0, 0};
	while (line[i])
	{
		if (!ft_isspecial_nq(line[i]))
			ft_find_noredir_word(base, line, &i);
		else if (ft_isredirection(line[i]))
			ft_find_redir_word(base, line, &i);
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
	}
}
