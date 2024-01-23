/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:53 by sbelomet          #+#    #+#             */
/*   Updated: 2023/11/29 11:10:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

/*
int	main(void)
{
	char str1[] = "Finn Mertens";
	char str2[] = "";

	printf("str1: %d\n", ft_strlen(str1));
	printf("str2: %d\n", ft_strlen(str2));
}*/
