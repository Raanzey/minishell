/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:00:00 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 16:56:04 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

void	*ft_exit(void)
{
	err_ext(0, "collector: ", ERR_CLC, 1);
	return (0);
}

t_memblock	*ft_add_new_block(void *data, size_t size)
{
	static t_memblock	*head;
	t_memblock			*new;
	t_memblock			*tmp;

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
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

void	ft_clear_all_blocks(t_memblock **head)
{
	t_memblock	*tmp;
	t_memblock	*node;

	if (!(*head))
		return ;
	node = *head;
	while (node)
	{
		tmp = node->next;
		if (node->data)
		{
			free(node->data);
			node->data = NULL;
		}
		free(node);
		node = tmp;
	}
	*head = NULL;
}
