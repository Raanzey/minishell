/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:58:04 by musisman          #+#    #+#             */
/*   Updated: 2025/07/03 01:58:42 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_UTILS_H
# define COLLECTOR_UTILS_H

# include "collector.h"

t_memblock	*ft_add_new_block(void *data, size_t size);
void		ft_clear_block(t_memblock **head);
size_t		ft_find_size(void *data);
void		*ft_exit(void);

#endif