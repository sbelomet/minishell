/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:26:22 by sbelomet          #+#    #+#             */
/*   Updated: 2024/03/01 09:50:14 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_printable(char *name, int type)
{
	if (ft_equal_strs(name, "_"))
		return (ONLY_ENV);
	if (ft_equal_strs(name, "?"))
		return (NONE);
	if (type == LIMBO)
		return (LIMBO);
	if (type == BOTH)
		return (BOTH);
	if (type == ONLY_ENV)
		return (ONLY_ENV);
	if (type == ONLY_EXPORT)
		return (ONLY_EXPORT);
	if (type == TO_BOTH)
		return (TO_BOTH);
	return (BOTH);
}

char	*ft_extract_var_name_strict(char *raw_name)
{
	int		start;
	int		len;
	int		i;
	char	*res;

	start = 1;
	i = 1;
	len = 0;
	while (raw_name[i] && !ft_isspecial(raw_name[i])
		&& raw_name[i] != '$' && raw_name[i] != ':')
	{
		i++;
		len++;
	}
	if (len == 1)
		return ("");
	res = ft_substr(raw_name, start, len);
	if (!res)
		return (NULL);
	return (res);
}

t_var	*ft_findvar(t_var *first_var, char *name)
{
	t_var	*res;

	res = first_var;
	while (res)
	{
		if (ft_equal_strs(name, res->name))
			return (res);
		res = res->next;
	}
	return (NULL);
}

char	*ft_findvar_value(t_base *base, char *name)
{
	t_var	*tmp;

	tmp = ft_findvar(base->first_var, ++name);
	if (tmp)
	{
		return (tmp->value);
	}
	return ("");
}
