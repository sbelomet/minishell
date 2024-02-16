/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/15 10:25:02 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_var_value(char *line, int start, int len, char **vars)
{
	char		*tmp;
	char		*res;
	static int	var_i = 0;

	//printf("var i : %d\n", var_i);
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
		while (line[++(*i)] && !ft_isspecial(line[*i]) && line[*i] != '$')
		{
		}
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
		ft_error(base, "malloc()");
	start = i;
	len = 0;
	while (line[i])
	{
		i++;
		len++;
	}
	tmp = ft_substr(line, start, len);
	if (!tmp)
		ft_error(base, "malloc()");
	res = ft_strjoin_free(res, tmp);
	if (!res)
		ft_error(base, "malloc()");
	//printf("time to return good string: %s\n", res);
	return (res);
}
