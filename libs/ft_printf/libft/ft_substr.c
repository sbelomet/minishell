/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:20:32 by sbelomet          #+#    #+#             */
/*   Updated: 2023/10/17 11:10:23 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	unsigned int	strlen;

	i = 0;
	strlen = (unsigned int)ft_strlen(s);
	if (len > (size_t)strlen)
		len = strlen;
	res = (char *)malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	if (start < strlen)
	{	
		while (s[i + start] && i < len)
		{
			res[i] = s[i + start];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

/*
int	main(void)
{
	printf("substring: |%s|\n", ft_substr("no nonozyes ye syes nono no", 8, 11));
}*/
