/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:11:46 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 10:33:14 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_value(t_base *base, char *var)
{
	int		i;
	int		start;
	char	*res;
	char	*tmp;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			start = i + 1;
		i++;
	}
	res = ft_substr(var, start, i - start);
	if (!res)
		return (NULL);
	if (*res == '$')
	{
		tmp = ft_strdup(ft_findvar_value(base, res));
		if (!tmp)
			return (NULL);
		free(res);
		return (tmp);
	}
	return (res);
}

char	*ft_get_var_name(t_base *base, char *var)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			res = ft_substr(var, 0, i);
			if (!res)
				return (NULL);
			if (*res == '$')
			{
				tmp = ft_strdup(ft_findvar_value(base, res));
				if (!tmp)
					return (NULL);
				free(res);
				return (tmp);
			}
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	ft_get_env_vars(t_base *base, char **env)
{
	int		i;
	char	*name;
	char	*value;
	t_var	*var;

	i = 0;
	while (env[i])
	{
		name = ft_get_var_name(base, env[i]);
		if (!name)
			ft_error(base, "malloc()");
		value = ft_get_var_value(base, env[i]);
		if (!value)
			ft_error(base, "malloc()");
		var = ft_new_var_node(name, value);
		if (!var)
			ft_error(base, "malloc()");
		ft_add_var_node(base, var);
		i++;
	}
}

void	ft_add_var(t_base *base, char *input)
{
	char	*name;
	char	*value;
	t_var	*var;
	t_var	*tmp;

	name = ft_get_var_name(base, input);
	if (!name)
		ft_error(base, "malloc()");
	value = ft_get_var_value(base, input);
	if (!value)
		ft_error(base, "malloc()");
	tmp = ft_findvar(base->first_var, name);
	if (tmp)
	{
		free(name);
		free(tmp->value);
		tmp->value = value;
		return ;
	}
	var = ft_new_var_node(name, value);
	if (!var)
		ft_error(base, "malloc()");
	ft_add_var_node(base, var);
}