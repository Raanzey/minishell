/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:00:00 by musisman          #+#    #+#             */
/*   Updated: 2025/07/20 16:02:04 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "collector.h"

void	*ft_exit(void)
{
	const char	*err = "collector: Out of memory\n";
	int			i;

	i = -1;
	while (err[++i])
		write(STDERR_FILENO, &err[i], 1);
	ft_free();
	exit(EXIT_FAILURE);
	return (NULL);
}

t_memblock	*ft_add_new_block(void *data, size_t size)
{
	static t_memblock	*head;
	t_memblock			*new;
	t_memblock			*node;

	new = malloc(sizeof(t_memblock));
	if (!new)
		return (ft_exit());
	new->data = data;
	new->size = size;
	new->head = &head;
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		node = head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new);
}

void	ft_clear_block(t_memblock **head)
{
	t_memblock	*temp;
	t_memblock	*node;

	if (!(*head))
		return ;
	node = *head;
	while (node)
	{
		temp = node->next;
		if (node->data)
		{
			free(node->data);
			node->data = NULL;
		}
		free(node);
		node = temp;
	}
	*head = NULL;
}

size_t	ft_find_size(void *data)
{
	t_memblock	*node;
	size_t		res;

	node = *(ft_add_new_block(NULL, 0)->head);
	while (1)
	{
		if (node->data == data)
			res = node->size;
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (res);
}
