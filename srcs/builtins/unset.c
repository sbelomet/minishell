/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:23 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 14:53:35 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_base *base, t_cmd *cmd)
{
	t_arg	*var_name;
	t_var	*var;

	var_name = cmd->first_arg;
	while (!var_name)
	{
		var = ft_findvar(base->first_var, var_name->name);
		ft_del_var_node(base, var);
		var_name = var_name->next;
	}
}
