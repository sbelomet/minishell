/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:51:34 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/26 10:14:31 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isintable(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;

	end = ft_strlen(s1);
	while (end > 0 && ft_isintable(set, s1[end - 1]))
		end--;
	start = 0;
	while (ft_isintable(set, s1[start]))
		start++;
	if (start >= end)
	{
		start = 0;
		end = 0;
	}
	res = (char *)malloc((end - start) * sizeof(char) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, (s1 + start), (end - start + 1));
	return (res);
}
