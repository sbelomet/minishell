/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:07:50 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long long a, int fd)
{
	int	count;

	write(fd, "0x", 2);
	count = 2;
	if (a == 0)
	{
		write(fd, "0", 1);
		return (3);
	}
	count += ft_printhex(a, 'x', fd);
	return (count);
}
