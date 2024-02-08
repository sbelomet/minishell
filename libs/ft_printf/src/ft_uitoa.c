/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:33:34 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	char	*res;
	int		numlen;

	numlen = ft_numlen(n);
	res = (char *)malloc(numlen * sizeof(char) + 1);
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	res[numlen] = '\0';
	while (n)
	{
		res[numlen - 1] = (n % 10) + '0';
		n /= 10;
		numlen--;
	}
	return (res);
}
