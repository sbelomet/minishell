/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:07:50 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/20 15:23:20 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printptr(unsigned long long a)
{
	int	count;

	write(1, "0x", 2);
	count = 2;
	if (a == 0)
	{
		write(1, "0", 1);
		return (3);
	}
	count += ft_printhex(a, 'x');
	return (count);
}
