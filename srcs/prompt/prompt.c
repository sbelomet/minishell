/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:27 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/29 15:04:19 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_line(t_base *base, char *line)
{
	int	error;

	ft_lexer_start(base, line);
	if (errors_lexer(base) != 1)
	{
		error = format_redirections(base);
		if (error == -2 || error == -3)
		{
			base->exit_status = EXIT_FAILURE;
			update_for_next_line(base);
			return ;
		}
		else
		{
			if (base->pipe == 1)
			{
				exec_pipes(base);
			}	
			else
			{
				exec_single_cmd(base);
			}
		}
	}
	update_for_next_line(base);
}

void	ft_print_exit(t_base *base, char *prompt)
{
	int		prompt_len;
	char	*len_in_char;
	char	*full_mess;
	char	*tmp;

	prompt_len = ft_strlen(prompt);
	len_in_char = ft_itoa(prompt_len);
	if (!len_in_char)
		ft_error(base);
	tmp = ft_strjoin("\033[", len_in_char);
	free(len_in_char);
	if (!tmp)
		ft_error(base);
	full_mess = ft_strjoin(tmp, "C");
	free(tmp);
	if (!full_mess)
		ft_error(base);
	printf("\033[1A");
	printf("%s", full_mess);
	free(full_mess);
	printf("exit\n");
	free(prompt);
}

void	ft_prompt(t_base *base)
{
	char	*rl;
	char	*prompt;
	char	*line;

	while (1)
	{
		ft_interactive_signals();
		g_signum = -1;
		prompt = ft_format_prompt(base);
		rl = readline(prompt);
		if (g_signum == SIGINT)
			update_exit_status(base, "1");
		if (!rl)
		{
			ft_print_exit(base, prompt);
			break ;
		}
		line = ft_strtrim(rl, " \n\t");
		if (ft_strlen(line) > 0)
		{
			add_history(rl);
			exec_line(base, line);
		}
		ft_free_after_prompt(base, rl, line, prompt);
	}
}
