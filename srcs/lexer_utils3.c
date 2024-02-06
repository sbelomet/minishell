/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/06 15:27:12 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_var_value(char *line, int start, int len, char **vars)
{
	char		*tmp;
	char		*res;
	static int	var_i = 0;

	printf("var i : %d\n", var_i);
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
	if (var_i >= ft_nb_vars_in_quotes(line) - 1)
		var_i = 0;
	return (res);
}

char	*ft_make_quoted_line(t_base *base, char **vars, char *line)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (line[i])
	{
		start = i;
		len = 0;
		i--;
		while (line[++i] && line[i] != '$')
			len++;
		printf("we finna segfault, len: %d\n", len);
		tmp = ft_join_var_value(line, start, len, vars);
		if (!tmp)
			ft_error(base, "malloc()");
		printf("tmp: %s, len: %d\n", tmp, len);
		res = ft_strjoin_free(res, tmp);
		if (!res)
			ft_error(base, "malloc()");
		printf("res: %s\n", res);
		while (line[++i] && !ft_isspecial(line[i]) && line[i] != '$')
		{
			printf("i: %d\n", i);
		}
	}
	printf("time to return good string: %s\n", res);
	return (res);
}
