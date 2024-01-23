/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/23 15:02:14 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_base	base;
	t_var	*tmp;
	char	*rl;
	int		i;

	base.env = env;
	base.first_var = NULL;
	ft_get_env_vars(&base, env);
	i = 0;
	while (i++ < 5)
	{
		rl = readline("minishell> ");
		ft_add_var(&base, rl);
		free(rl);
	}
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
