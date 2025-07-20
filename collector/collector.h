/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:58:21 by musisman          #+#    #+#             */
/*   Updated: 2025/07/20 21:45:10 by musisman         ###   ########.fr       */
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

t_memblock	*ft_add_new_block(void *data, size_t size);
void		ft_clear_block(t_memblock **head);
size_t		ft_find_size(void *data);
void		*ft_exit(void);
void		*ft_malloc(size_t size);
void		*ft_calloc(size_t count, size_t size);
void		*ft_realloc(void *old_data, size_t new_size);
void		ft_free(void);
void		*ft_absorb(void *addr);

#endif