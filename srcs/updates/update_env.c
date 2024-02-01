/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:32:09 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 10:13:07 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_env(t_base *base, char *name, char *new_value)
{
	t_var	*var;

	if (!new_value)
		return (1);
	var = ft_findvar(base, name);
	if (!var)
		return (1);
	if (var->value)
		free(var->value);
	var->value = new_value;
	return (0);
}