/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_methods.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:13:46 by musisman          #+#    #+#             */
/*   Updated: 2025/07/10 17:13:46 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_METHODS_H
# define  LEAK_METHODS_H

#include <stdlib.h>

typedef struct s_memory
{
        void *data;
        struct  s_memory *next;
} t_memory;

void	*ft_malloc(size_t size);
void	*ft_calloc(size_t type, size_t size);
void	*ft_realloc(void *before, size_t new_size);
void	ft_free(void);

#endif