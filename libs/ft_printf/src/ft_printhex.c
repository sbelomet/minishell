/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:17:23 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen(unsigned long long a)
{
	int	i;

	i = 0;
	while (a)
	{
		a /= 10;
		i++;
	}
	return (i);
}

static void	ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (j > i)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

int	ft_printhex(unsigned long long a, char isupper, int fd)
{
	int		i;
	int		count;
	char	*res;

	count = 0;
	i = 0;
	res = (char *)ft_calloc(ft_numlen(a) + 1, sizeof(char));
	if (!res)
		return (0);
	if (!a)
	{
		ft_putchar_fd('0', fd);
		count++;
	}
	while (a)
	{
		res[i] = ft_converthex((int)(a % 16), isupper);
		a /= 16;
		count++;
		i++;
	}
	ft_strrev(res);
	ft_putstr_fd(res, fd);
	free(res);
	return (count);
}
