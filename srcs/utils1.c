/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:13:24 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/23 14:58:01 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_base base)
{
	t_var	*tmp1;
	t_var	*tmp2;

	tmp1 = base.first_var;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1->name);
			free(tmp1->value);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
}
