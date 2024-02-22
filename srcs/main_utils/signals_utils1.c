/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:53:07 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/22 11:56:20 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_slash(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
}

void	ft_ctrl_c1(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	g_error = 1;
}

void	ft_ctrl_c2(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	ft_ctrl_c3(int signum)
{
	(void)signum;
	exit(1);
}

void	ft_signals(void)
{
	signal(SIGINT, ft_ctrl_c1);
	signal(SIGQUIT, SIG_IGN);
}
