/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/28 15:41:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_my_damn_quotes(t_base *base, char *line)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (*line == '"')
	{
		tmp = ft_strtrim(line, "\"");
		if (!tmp)
			ft_error(base);
		res = ft_get_developped_vars(base, tmp);
		if (!res)
			ft_error(base);
	}
	else if (*line == '\'')
	{
		res = ft_strtrim(line, "'");
		if (!res)
			ft_error(base);
	}
	return (res);
}

char	*ft_join_var_value(char *line, int start, int len, char **vars)
{
	char		*tmp;
	char		*res;
	static int	var_i = 0;

	tmp = ft_substr(line, start, len);
	if (!tmp)
		return (NULL);
	if (vars[var_i])
	{
		res = ft_strjoin(tmp, vars[var_i]);
		if (!res)
			return (NULL);
	}
	else
		res = ft_strdup(tmp);
	free(tmp);
	var_i++;
	if (var_i >= ft_nb_vars_in_quotes(line))
		var_i = 0;
	return (res);
}

char	*ft_start_quoted_line(char **vars, char *line, int nb_vars, int *i)
{
	int		start;
	int		len;
	char	*tmp;
	char	*res;

	res = ft_strdup("");
	while (nb_vars)
	{
		start = *i;
		len = 0;
		(*i)--;
		while (line[++(*i)] && line[*i] != '$')
			len++;
		tmp = ft_join_var_value(line, start, len, vars);
		if (!tmp)
			return (NULL);
		res = ft_strjoin_free(res, tmp);
		if (!res)
			return (NULL);
		while (line[++(*i)] && !ft_isspecial(line[*i])
			&& line[*i] != '$' && line[*i] != ':')
			continue ;
		nb_vars--;
	}
	return (res);
}

char	*ft_make_quoted_line(t_base *base, char **vars, char *line, int nvars)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*res;

	i = 0;
	res = ft_start_quoted_line(vars, line, nvars, &i);
	if (!res)
		ft_error(base);
	start = i;
	len = 0;
	while (line[i])
	{
		i++;
		len++;
	}
	tmp = ft_substr(line, start, len);
	if (!tmp)
		ft_error(base);
	res = ft_strjoin_free(res, tmp);
	if (!res)
		ft_error(base);
	return (res);
}

char	*ft_extract_to_quote(t_base *base, char *line, int *index)
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
	res = ft_substr(line, start, len);
	if (!res)
		ft_error(base);
	if (ft_strchr(res, '$'))
	{
		tmp = ft_strdup(res);
		free(res);
		res = ft_get_developped_vars(base, tmp);
		return (res);
	}
	return (res);
}
