/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:34:24 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/29 10:42:34 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nb_vars_in_quotes(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*ft_extract_var_name(char *line, int *i)
{
	int		start;
	int		len;
	char	*res;

	start = *i;
	(*i)++;
	len = 1;
	while (line[*i] && !ft_isspecial(line[*i])
		&& line[*i] != '$' && line[*i] != ':')
	{
		(*i)++;
		len++;
	}
	if (len == 1)
		return ("");
	res = ft_substr(line, start, len);
	if (!res)
		return (NULL);
	return (res);
}

void	ft_develop_var(t_base *base, char **vars, char *line, int *i)
{
	static int	var_i = 0;
	char		*name;

	name = ft_extract_var_name(line, i);
	if (!name)
		ft_error(base);
	vars[var_i] = ft_strdup(ft_findvar_value(base, name));
	if (!vars[var_i])
		ft_error(base);
	var_i++;
	free(name);
	if (var_i >= ft_nb_vars_in_quotes(line))
		var_i = 0;
}

char	*ft_get_developped_vars(t_base *base, char *line)
{
	int		i;
	int		nb_vars;
	char	*res;
	char	**vars;

	i = 0;
	nb_vars = ft_nb_vars_in_quotes(line);
	vars = (char **)malloc(sizeof(char *) * (nb_vars + 1));
	if (!vars)
		ft_error(base);
	while (line[i])
	{
		if (line[i] == '$')
			ft_develop_var(base, vars, line, &i);
		else
			i++;
	}
	vars[nb_vars] = NULL;
	res = ft_make_quoted_line(base, vars, line, nb_vars);
	ft_free_array(vars);
	free(line);
	return (res);
}

char	*ft_extract_quotes(t_base *base, char *line, int *i, char quote)
{
	int		len;
	int		start;
	char	*res;

	len = 0;
	if (*i < ft_strlen(line) - 1)
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
		len++;
		if (!line[*i])
			break ;
	}
	res = ft_substr(line, start, len);
	if (!res)
		ft_error(base);
	if (quote == '"')
		res = ft_get_developped_vars(base, res);
	if (ft_isquote(line[*i]))
		(*i)++;
	return (res);
}
