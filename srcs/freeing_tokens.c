/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:40:12 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/31 14:42:50 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_base base)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = base.first_token;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			/* if (tmp1->type)
				free(tmp1->type); */
			free(tmp1);
			tmp1 = tmp2;
		}
	}	
}
