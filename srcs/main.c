/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/24 13:52:56 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_curdir(t_base *base)
{
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	ft_revstr(pwd);
	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
		{
			base->curdir = ft_substr(pwd, 0, i);
			ft_revstr(base->curdir);
			free(pwd);
			return ;
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_base	base;
	t_var	*tmp;

	base.env = env;
	base.first_var = NULL;
	ft_get_env_vars(&base, env);
	ft_get_curdir(&base);
	ft_prompt(&base);
	tmp = base.first_var;
	while (tmp)
	{
		printf("NAME: %s\nVALUE: %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	ft_free(base);
	(void)ac;
	(void)av;
	return (0);
}
