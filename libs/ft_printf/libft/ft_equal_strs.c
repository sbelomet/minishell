/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_equal_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:32:44 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 11:38:07 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_equal_strs(const char *s1, const char *s2, int size)
{
	int	i;

	if (size < 0)
		size = ft_strlen(s1);
	i = 0;
	while (s1[i] && s2[i] && i < size)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (i != size)
		return (0);
	return (1);
}