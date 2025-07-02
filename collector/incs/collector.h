/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:58:21 by musisman          #+#    #+#             */
/*   Updated: 2025/07/03 01:58:23 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include <stddef.h>

typedef struct s_memblock
{
	void				*data;
	size_t				size;
	struct s_memblock	**head;
	struct s_memblock	*next;

}						t_memblock;

void					*ft_malloc(size_t size);
void					*ft_calloc(size_t type, size_t size);
void					*ft_realloc(void *old_data, size_t new_size);
void					ft_free(void);
void					*ft_absorb(void *addr);

#endif