/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converthex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:37:42 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/20 15:27:24 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	ft_converthex(int a, char isupper)
{
	if (a <= 9 && a >= 0)
		return ((char)(a + '0'));
	if (a <= 15 && a >= 10 && isupper == 'x')
		return ((char)((a % 10) + 'a'));
	if (a <= 15 && a >= 10 && isupper == 'X')
		return ((char)((a % 10) + 'A'));
	return (0);
}
