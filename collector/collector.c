/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:59:35 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 16:41:21 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (ft_exit());
	ft_add_new_block(res, size);
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;

	res = malloc(size * count);
	if (!res)
		return (ft_exit());
	ft_bzero(res, count * size);
	ft_add_new_block(res, size * count);
	return (res);
}

void	ft_free(void)
{
	ft_clear_all_blocks(ft_add_new_block(NULL, 0)->head);
}
