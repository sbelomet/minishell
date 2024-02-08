/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:58:43 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 10:35:30 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_word(t_base *base, char *line, int *index, char *in_quotes)
{
	int		start;
	int		len;
	char	*res;
	char	*tmp;

	if (in_quotes)
		return (in_quotes);
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

void	ft_find_noredir_word(t_base *base, char *line, int *i, char *in_quotes)
{
	char		*token;
	t_lexvars	*lexvars;

	lexvars = &base->lexvars;
	token = ft_extract_word(base, line, i, in_quotes);
	printf("token: %s\n", token);
	if (!token)
		ft_error(base, "malloc()");
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
		ft_error(base, "malloc()");
	if (*token == '<' || *token == '>')
		base->lexvars.after_redir = 1;
	base->lexvars.after_cmd = 0;
	ft_tokenize(base, token, TOKEN_REDIR);
}

void	ft_lexer_start(t_base *base, char *line)
{
	int		i;
	char	*in_quotes;

	i = 0;
	base->lexvars = (t_lexvars){0, 0};
	while (line[i])
	{
		in_quotes = NULL;
		if (ft_isquote(line[i]))
		{
			printf("getting inquotes\n");
			in_quotes = ft_extract_quotes(base, line, &i, line[i]);
			printf("inquotes: %s, i: %d\n", in_quotes, i);
			ft_find_noredir_word(base, line, &i, in_quotes);
		}
		else if (!ft_isspecial(line[i]))
			ft_find_noredir_word(base, line, &i, NULL);
		else if (ft_isredirection(line[i]))
			ft_find_redir_word(base, line, &i);
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
	}
}
