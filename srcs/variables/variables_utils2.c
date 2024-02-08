/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:26:22 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:22:02 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_findvar_value(t_base *base, char *name)
{
	t_var	*tmp;
	char	*ctmp;

	if (ft_equal_strs(name, "$?"))
	{
		ctmp = ft_itoa(g_error);
		if (!malloc_add(&base->alloc, malloc_new(ctmp)))
			ft_error(base, "malloc()");
		if (!ctmp)
			ft_error(base, "malloc()");
		return (ctmp);
	}
	tmp = ft_findvar(base->first_var, ++name);
	if (tmp)
		return (tmp->value);
	return ("");
}
