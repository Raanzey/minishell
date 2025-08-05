/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:19:30 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:32:49 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmini.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
