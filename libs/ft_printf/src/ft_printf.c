/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:31:11 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		len;

	va_start(args, format);
	i = 0;
	count = 0;
	len = ft_strlen(format);
	while (format[i])
	{
		while (format[i] == '%')
		{
			count += ft_printformat(args, format[i + 1], fd);
			i += 2;
		}
		if (i < len)
		{
			ft_putchar_fd(format[i], fd);
			i++;
			count++;
		}
	}
	va_end(args);
	return (count);
}

/*
int	main(void)
{
	ft_printf("\n");
	printf("\nfcount: %d\n", ft_printf("%%"));
	printf("\nfcount: %d\n", printf("%%"));
}*/
