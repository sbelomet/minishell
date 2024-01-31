/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:11:46 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/31 10:53:57 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_value(char *var)
{
	int		i;
	int		start;
	char	*res;

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
	return (res);
}

char	*ft_get_var_name(char *var)
{
	int		i;
	char	*res;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			res = ft_substr(var, 0, i);
			if (!res)
				return (NULL);
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
		name = ft_get_var_name(env[i]);
		if (!name)
			ft_error(base, "malloc()");
		value = ft_get_var_value(env[i]);
		if (!value)
			ft_error(base, "malloc()");
		var = ft_new_var_node(name, value);
		if (!var)
			ft_error(base, "malloc()");
		ft_add_var_node(base, var);
		i++;
	}
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

void	ft_add_var(t_base *base, char *input)
{
	char	*name;
	char	*value;
	t_var	*var;
	t_var	*tmp;

	name = ft_get_var_name(input);
	if (!name)
		ft_error(base, "malloc()");
	value = ft_get_var_value(input);
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
