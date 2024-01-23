/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:55:46 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/24 11:08:56 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_printint(int n)
{
	int		count;
	char	*s;

	count = 0;
	s = ft_itoa(n);
	count += ft_printstr(s);
	free(s);
	return (count);
}

static int	ft_printuint(unsigned int n)
{
	int		count;
	char	*s;

	count = 0;
	s = ft_uitoa(n);
	count += ft_printstr(s);
	free(s);
	return (count);
}

int	ft_printformat(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		count++;
	}
	else if (format == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (format == '%')
	{
		ft_putchar_fd('%', 1);
		count++;
	}
	else if (format == 'p')
		count += ft_printptr((unsigned long long)va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += ft_printint(va_arg(args, int));
	else if (format == 'u')
		count += ft_printuint(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_printhex((unsigned long long)va_arg(args, unsigned int),
				format);
	return (count);
}
