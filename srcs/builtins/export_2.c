/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:27:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/22 15:57:40 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_exist(t_var *env, char *name)
{
	while (env)
	{
		if (ft_equal_strs(env->name, name))
			return (1);
		env = env->next;
	}
	return (0);
}

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
	status_env = ft_new_var_node(name, value, 1, 0);
	if (!status_env)
		ft_error(base);
	ft_add_var_node(base, status_env);
	return (0);
}

int	add_without_equal(t_base *base, char **array)
{
	char	*name;
	char	*value;
	t_var	*status_env;

	name = ft_strdup(array[0]);
	if (!name)
		ft_error(base);
	value = NULL;
	status_env = ft_new_var_node(name, value, 3, 1);
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
	if (var->value)
	{
		free(var->value);
		var->value = ft_strdup(array[1]);
	}
	else
		var->value = ft_strdup(array[1]);
	return (0);
}

void	add_export(t_base *base, char **array, int equal)
{
	if (!array)
		return ;
	if (check_if_exist(base->first_var, array[0]) == 0)
	{
		printf("DEBBUG01 add\n");
		add_var_export(base, array, equal);
		//update tab env
	}
	else
	{
		printf("DEBBUG01 update\n");
		update_var_export(base, array);
		// update tab env
	}
	// free array
}