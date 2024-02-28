/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:21:49 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/28 12:18:55 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_slash(int signum)
{
	(void)signum;
	write(1, "^\\Quit: 3\n", 10);
}

void	ft_ctrl_c1(int signum)
{
	g_signum = signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_ctrl_c2(int signum)
{
	(void)signum;
	write(1, "^C\n", 3);
}

void	ft_ctrl_c3(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
