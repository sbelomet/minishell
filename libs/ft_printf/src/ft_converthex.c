/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converthex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:37:42 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:48:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
