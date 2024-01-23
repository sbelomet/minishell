/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:16:25 by sbelomet          #+#    #+#             */
/*   Updated: 2023/11/29 13:29:42 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int count, int size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	p = ft_memset(p, '\0', count * size);
	return (p);
}

/*
int	main(void)
{
	int	*p;
	int	i;

	p = (int *)ft_calloc(5, sizeof(int));
	i = 0;
	while (p[i])
	{
		write(1, p[i], 8);
		i++;
	}
}*/
