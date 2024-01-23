/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:31:11 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/24 13:07:12 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf(const char *format, ...)
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
			count += ft_printformat(args, format[i + 1]);
			i += 2;
		}
		if (i < len)
		{
			ft_putchar_fd(format[i], 1);
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
