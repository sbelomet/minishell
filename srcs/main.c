/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/07 14:18:04 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_banner(void)
{
	ft_printf("\e[1;1H\e[2J");
	ft_printf("   __  ___ ____ _  __ ____ ____ __ __ ____ __    __ \n");
	ft_printf("  /  |/  //  _// |/ //  _// __// // // __// /   / / \n");
	ft_printf(" / /|_/ /_/ / /    /_/ / _\\ \\ / _  // _/ / /__ / /__\n");
	ft_printf("/_/  /_//___//_/|_//___//___//_//_//___//____//____/\n");
	write(1, "\n", 1);
}

int	main(int ac, char **av, char **env)
{
	t_base	base;

	(void)ac;
	(void)av;
	ft_banner();
	ft_base_init(&base, env);
	ft_prompt(&base);
	ft_free(base);
}
