/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:27:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/01 10:15:08 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_with_equal(t_base *base, char **array)
{
	char	*name;
	char	*value;
	t_var	*status_env;

	name = ft_strdup(array[0]);
	if (!name)
		ft_error(base);
	if (array[1])
		value = ft_strdup(array[1]);
	else
		value = ft_strdup("");
	if (!value)
		ft_error(base);
	status_env = ft_new_var_node(name, value, TO_BOTH, 0);
	if (!status_env)
		ft_error(base);
	ft_add_var_node(base, status_env);
	return (0);
}

static int	add_without_equal(t_base *base, char **array)
{
	char	*name;
	t_var	*status_env;

	name = ft_strdup(array[0]);
	if (!name)
		ft_error(base);
	status_env = ft_new_var_node(name, NULL, ONLY_EXPORT, 1);
	if (!status_env)
		ft_error(base);
	ft_add_var_node(base, status_env);
	return (0);
}

static int	add_var_export(t_base *base, char **array, int equal)
{
	if (equal == 1)
	{
		if (add_with_equal(base, array) == -1)
			return (-1);
	}
	else
	{
		if (add_without_equal(base, array) == -1)
			return (-1);
	}
	return (0);
}

static int	update_var_export(t_base *base, char **array)
{
	t_var	*var;

	var = ft_findvar(base->first_var, array[0]);
	if (!var)
		return (0);
	if (var->printable == ONLY_EXPORT
		|| var->printable == LIMBO)
		var->printable = BOTH;
	if (var->standalone && array[1])
		var->standalone = 0;
	if (array[1])
	{
		free(var->value);
		var->value = ft_strdup(array[1]);
	}
	return (0);
}

void	add_export(t_base *base, char **array, int equal)
{
	int	i;

	if (!array)
		return ;
	if (check_if_exist(base->first_var, array[0]) == 0)
	{
		add_var_export(base, array, equal);
		update_tab_env_export(base);
	}
	else
	{
		update_var_export(base, array);
		update_tab_env_export(base);
	}
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
