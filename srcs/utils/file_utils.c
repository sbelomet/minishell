/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:35:59 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:11:51 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *path, int type)
{
	int	file;

	file = 0;
	if (type == 0)
		file = open(path, O_RDONLY, 0644);
	if (type == 1)
		file = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == 2)
		file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		perror(path);
		return (-1);
	}
	return (file);
}
