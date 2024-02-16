/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:40:12 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/16 11:05:33 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_args(t_arg *first_arg)
{
	t_arg	*tmp1;

	while (first_arg)
	{
		tmp1 = first_arg->next;
		if (first_arg->name)
			free(first_arg->name);
		free(first_arg);
		first_arg = tmp1;
	}
}

void	ft_free_command(t_cmd *cmd)
{
	//printf("before freeing command\n");
	if (cmd)
	{
		if (cmd->path)
		{
			//printf("after freeing path\n");
			free(cmd->path);
		}
		if (cmd->name)
		{
			//printf("after freeing name\n");
			free(cmd->name);
		}
		if (cmd->first_arg)
		{
			//printf("after freeing firstarg\n");
			ft_free_args(cmd->first_arg);
		}
		free(cmd);
	}
}

void	ft_free_redirection(t_redir *redir)
{
	//printf("before freeing redir\n");
	if (redir)
	{
		if (redir->name)
		{
			//printf("after freeing name\n");
			free(redir->name);
		}
		if (redir->limiter)
		{
			//printf("after freeing limiter\n");
			free(redir->limiter);
		}
		if (redir->filepath)
		{
			//printf("after freeing file\n");
			free(redir->filepath);
		}
		free(redir);
	}
}

void	ft_free_tokens(t_token *first_token)
{
	t_token	*tmp1;
	t_token	*tmp2;
	int		id;

	tmp1 = first_token;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			id = tmp1->id;
			//printf("before checking\n");
			if (id == TOKEN_BUILTIN || id == TOKEN_BIN)
				ft_free_command(tmp1->type);
			else if (id == TOKEN_UNKNOWN_REDIR || id == TOKEN_REDIR_IN
				|| id == TOKEN_REDIR_OUT
				|| id == TOKEN_REDIR_APP || id == TOKEN_REDIR_HDOC
				|| id == TOKEN_PIPE || id == TOKEN_AND || id == TOKEN_OR)
				ft_free_redirection(tmp1->type);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
}
