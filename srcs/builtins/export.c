/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:05 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 10:25:30 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_base *base, t_cmd *cmd)
{
	if (base && cmd)
		return (1);
	return (0);
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