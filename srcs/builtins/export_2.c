/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:27:27 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 14:02:03 by lgosselk         ###   ########.fr       */
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

/*int		update_var_export(t_base *base, t_arg *args, char **arraymake )
{
	t_var	*var;

	var = ft_findvar(base->first_var, name);
	if (var->value)
	{
		free(var->value);
		var->value = ft_strdup(ar)
	}
}*/

void	add_export(t_base *base, t_arg *args, char **array)
{
	//int	j;

	if (check_if_exist(base->first_var, array[0]) == 0)
	{
		//new
		if (args)
			return ;
	}
	else
	{
		
	}
}