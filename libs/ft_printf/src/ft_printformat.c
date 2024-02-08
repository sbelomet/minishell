/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:55:46 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printint(int n, int fd)
{
	int		count;
	char	*s;

	count = 0;
	s = ft_itoa(n);
	count += ft_printstr(s, fd);
	free(s);
	return (count);
}

static int	ft_printuint(unsigned int n, int fd)
{
	int		count;
	char	*s;

	count = 0;
	s = ft_uitoa(n);
	count += ft_printstr(s, fd);
	free(s);
	return (count);
}

int	ft_printformat(va_list args, char format, int fd)
{
	int	count;

	count = 0;
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		count++;
	}
	else if (format == 's')
		count += ft_printstr(va_arg(args, char *), fd);
	else if (format == '%')
	{
		ft_putchar_fd('%', fd);
		count++;
	}
	else if (format == 'p')
		count += ft_printptr((unsigned long long)va_arg(args, void *), fd);
	else if (format == 'd' || format == 'i')
		count += ft_printint(va_arg(args, int), fd);
	else if (format == 'u')
		count += ft_printuint(va_arg(args, unsigned int), fd);
	else if (format == 'x' || format == 'X')
		count += ft_printhex((unsigned long long)va_arg(args, unsigned int),
				format, fd);
	return (count);
}
