/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:09:42 by sbelomet          #+#    #+#             */
/*   Updated: 2023/11/22 15:59:13 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
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

static int	ft_specialnum(char *res, int n)
{
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	if (n == 0)
		res[0] = '0';
	return (n);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		num;
	int		numlen;

	numlen = ft_numlen(n);
	res = (char *)malloc(numlen * sizeof(char) + 1);
	if (!res)
		return (NULL);
	num = ft_specialnum(res, n);
	res[numlen] = '\0';
	while (num)
	{
		res[numlen - 1] = (num % 10) + '0';
		num /= 10;
		numlen--;
	}
	return (res);
}

/*
int	main(void)
{
	printf("num: |%s|\n", ft_itoa(0));
}*/
