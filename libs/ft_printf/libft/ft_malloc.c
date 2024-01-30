/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:25:24 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 10:14:22 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_malloc_clear(t_alloc **lst)
{
	t_alloc	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->ptr)
				free((*lst)->ptr);
			free(*lst);
			*lst = tmp;
		}
	}
}

t_alloc	*malloc_new(void *content)
{
	t_alloc	*node;

	node = (t_alloc *) malloc(sizeof(t_alloc));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->ptr = content;
	return (node);
}

int	malloc_add(t_alloc **lst, t_alloc *new_node)
{
	t_alloc	*temp;

	if (new_node == NULL)
		return (0);
	temp = *lst;
	if (temp == NULL)
	{
		*lst = new_node;
		return (1);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (1);
}

void	*ft_malloc(int size, t_alloc **lst)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		return (NULL);
	if (!malloc_add(lst, malloc_new(alloc)))
		return (NULL);
	return (alloc);
}
