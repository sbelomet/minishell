/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:32:07 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 14:25:30 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*get_last_cmd(t_cmds *cmds)
{
	t_cmds	*temp;

	if (!cmds)
		return (cmds);
	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
	}
	return (temp);
}

void	add_command(t_base *base, t_cmds **cmds, t_cmd *cmd)
{
	t_cmds	*new_cmd;
	t_cmds	*last_cmd;

	if (cmds == NULL)
		return ;
	new_cmd = (t_cmds *) malloc(sizeof(t_cmds));
	if (!new_cmd)
		ft_error(base);
	new_cmd->cmd = cmd;
	new_cmd->next = NULL;
	if (*cmds == NULL)
		*cmds = new_cmd;
	else
	{
		last_cmd = get_last_cmd(*cmds);
		last_cmd->next = new_cmd;
	}
}

t_cmds	*push_commands(t_base *base)
{
	t_cmds	*cmds;
	t_token	*token;

	cmds = NULL;
	token = get_first_token(base);
	while (token)
	{
		if (is_token_cmd(token))
			add_command(base, &cmds, get_token_class(token));
		token = token->next;
	}
	return (cmds);
}

void	free_nodes(t_base *base)
{
	t_cmds	*cmds;
	t_cmds	*temp;

	if (base->cmds == NULL)
		return ;
	cmds = base->cmds;
	while (cmds)
	{
		temp = cmds->next;
		free(cmds);
		cmds = temp;
	}
	base->cmds = NULL;
}
