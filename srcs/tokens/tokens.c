/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:16:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/23 10:19:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_cmd(t_base *base, char *cmd)
{
	t_token	*res;
	char	*path;

	path = NULL;
	res = ft_new_token_node(TOKEN_WORD);
	if (!res)
		ft_error(base);
	ft_add_token_node(base, res);
	if (ft_equal_strs(cmd, ""))
		res->id = TOKEN_WORD;
	else if (ft_isbuiltin(cmd))
		res->id = TOKEN_BUILTIN;
	else if (ft_isbin(base, cmd))
	{	
		res->id = TOKEN_BIN;
		path = ft_get_cmdpath(base, cmd, res->id);
	}
	res->type = ft_new_cmd_node(res->id, path, cmd);
	if (!res->type)
		ft_error(base);
	if (res->id == TOKEN_WORD)
		res->id = TOKEN_BIN;
}

void	ft_add_cmd_arg(t_base *base, char *arg)
{
	t_token	*cmd_token;
	t_cmd	*cmd;
	t_arg	*arg_node;

	cmd_token = ft_last_token(base->first_token);
	cmd = (t_cmd *)cmd_token->type;
	arg_node = ft_new_arg_node(TOKEN_ARG, arg);
	if (!arg_node)
		ft_error(base);
	ft_add_arg_node(cmd, arg_node);
}

void	ft_tokenize_redir(t_base *base, char *redir)
{
	t_token	*res;

	res = ft_new_token_node(ft_get_redir(redir));
	if (!res)
		ft_error(base);
	ft_add_token_node(base, res);
	res->type = ft_new_redir_node(res->id, redir);
	if (!res->type)
		ft_error(base);
	if (*redir == '|')
		base->pipe = 1;
}

void	ft_add_redir_file(t_base *base, char *file)
{
	t_token	*redir_token;
	t_redir	*redir;

	redir_token = ft_last_token(base->first_token);
	redir = (t_redir *)redir_token->type;
	if (redir->id == TOKEN_REDIR_HDOC)
		redir->limiter = file;
	else
		redir->filepath = file;
}

void	ft_tokenize(t_base *base, char *val, int id)
{
	if (id == TOKEN_CMD)
	{
		ft_tokenize_cmd(base, val);
	}
	else if (id == TOKEN_ARG)
	{
		ft_add_cmd_arg(base, val);
	}
	else if (id == TOKEN_REDIR)
	{
		ft_tokenize_redir(base, val);
	}
	else if (id == TOKEN_FILE)
	{
		ft_add_redir_file(base, val);
	}
	else if (id == TOKEN_VAR)
	{
		ft_add_var(base, val);
		free(val);
	}
}
