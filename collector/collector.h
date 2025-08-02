/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:58:21 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 16:46:24 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minishell.h"

typedef struct s_memblock
{
	void				*data;
	size_t				size;
	struct s_memblock	**head;
	struct s_memblock	*next;

}						t_memblock;

t_memblock	*ft_add_new_block(void *data, size_t size);
void		ft_clear_all_blocks(t_memblock **head);
void		*ft_exit(void);
void		*ft_malloc(size_t size);
void		*ft_calloc(size_t count, size_t size);
void		ft_free(void);

#endif