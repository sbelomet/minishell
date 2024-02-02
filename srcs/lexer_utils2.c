/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:34:24 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/02 15:44:53 by sbelomet         ###   ########.fr       */
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

char	*ft_get_developped_vars(t_base *base, char *line)
{
	int		i;
	int		var_i;
	char	*tmp;
	char	*var;
	char	**vars;

	i = 0;
	vars = (char **)malloc(sizeof(char *) * (ft_nb_vars_in_quotes(line) + 1));
	if (!vars)
		ft_error(base, "malloc()");
	var_i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			ft_extract_var_name(line, &i);
			vars[var_i] = ft_findvar_value(base, );
		}
		i++;
	}
	if (!tmp)
		ft_error(base, "malloc()");
	
}

char	*ft_extract_quotes(t_base *base, char *line, int *i, char quote)
{
	int		len;
	int		start;
	char	*res;
	char	*tmp;

	len = 0;
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
		len++;
	}
	res = ft_substr(line, start, len);
	if (!res)
		ft_error(base, "malloc()");
	if (quote == '"')
	{
		res = ft_develop_vars(base, res);
	}
	return (res);
}
