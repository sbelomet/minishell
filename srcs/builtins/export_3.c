/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:10:17 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/27 14:08:56 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_export_error(t_base *base, t_arg *arg)
{
	base->exit_status = 1;
	ft_printf(2, "export: '%s': not a valid identifier\n", arg->name);
}

int	ft_length_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char	**add_to_tab_env(t_base *base, t_var *var)
{
	int		i;
	char	*new_var;
	char	**new_tab;

	new_tab = (char **) ft_malloc((ft_length_tab(base->env) + 2)
			* sizeof(char *), &base->alloc);
	if (!new_tab)
		ft_error(base);
	new_var = ft_triple_strjoin(var->name, "=", var->value);
	if (!new_var)
		ft_error(base);
	i = -1;
	while (base->env[++i])
	{
		new_tab[i] = ft_strdup_allocated(base->env[i], &base->alloc);
		if (!new_tab[i])
			ft_error(base);
	}
	new_tab[i++] = new_var;
	free(new_var);
	new_tab[i] = NULL;
	return (new_tab);
}

void	update_tab_env_export(t_base *base)
{
	t_var	*vars;

	vars = base->first_var;
	while (vars)
	{
		if (vars->printable == TO_BOTH)
		{
			vars->printable = BOTH;
			base->env = add_to_tab_env(base, vars);
			if (!base->env)
				ft_error(base);
		}
		vars = vars->next;
	}
}
