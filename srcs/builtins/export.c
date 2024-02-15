/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:05 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 14:09:19 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_join(t_base *base, char *name, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin("declare -x ", name);
	if (!tmp)
		ft_error(base, "malloc()");
	res = ft_strjoin(tmp, "=\"");
	if (!res)
		ft_error(base, "malloc()");
	free(tmp);
	tmp = ft_strjoin(res, value);
	if (!tmp)
		ft_error(base, "malloc()");
	free(res);
	res = ft_strjoin(tmp, "\"");
	if (!res)
		ft_error(base, "malloc()");
	free(tmp);
	return (res);
}

void	ft_print_export(t_base *base)
{
	t_var	*var;
	char	*tmp;

	var = base->first_var;
	while (var)
	{
		tmp = ft_export_join(base, var->name, var->value);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		var = var->next;
		free(tmp);
		tmp = NULL;
	}
}

int	export(t_base *base, t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (!arg)
		ft_print_export(base);
	return (1);
}

// j'ai eliminer format_builtins.c, utilise cette function si tu veux. 
/*static void	format_export(t_cmd *cmd)
{
	int		i;
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (!arg)
		return ;
	while (arg)
	{
		i = -1;
		while (arg->name[++i])
		{
			if (arg->name[i] == '=' && !arg->name[i + 1])
			{
				arg = arg->next;
				if (arg)
					ft_printf(1, "export: '%s': not a valid identifier\n",
						arg->name);
			}
		}
		arg = arg->next;
	}
}*/