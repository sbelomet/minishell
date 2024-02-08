/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:53:07 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:32:12 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_slash(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	ft_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_error = 1;
}

void	ft_signals(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_slash);
}