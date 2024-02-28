/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:58:04 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/28 16:02:46 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_shlvl(t_base *base, int shlvl, char *free_me)
{
	char	*res;
	char	*shlvl_char;

	free(free_me);
	if (++shlvl > 999)
		shlvl = 0;
	shlvl_char = ft_itoa(shlvl);
	if (!shlvl_char)
		ft_error(base);
	res = ft_strjoin_alloc("SHLVL=", shlvl_char, &base->alloc);
	if (!res)
		ft_error(base);
	free(shlvl_char);
	return (res);
}

void	ft_incr_shell_level(t_base *base)
{
	int		i;
	int		j;
	char	*shlvl;
	int		shlvl_int;

	i = -1;
	while (base->env[++i])
	{
		if (ft_strnstr(base->env[i], "SHLVL=", 6))
		{
			j = 6;
			while (base->env[i][j])
				j++;
			if (j != 6)
			{
				shlvl = ft_substr(base->env[i], 6, j);
				if (!shlvl)
					ft_error(base);
				shlvl_int = ft_atoi(shlvl);
				base->env[i] = ft_strjoin_shlvl(base, shlvl_int, shlvl);
			}
			break ;
		}
	}
}
