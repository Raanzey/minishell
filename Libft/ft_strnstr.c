/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:06:47 by musisman          #+#    #+#             */
/*   Updated: 2024/10/19 21:26:30 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;

	a = (char *)haystack;
	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return (a);
	while (a[i] && i < len)
	{
		j = 0;
		while (i + j < len && a[i + j] == needle[j] && a[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (a + i);
		i++;
	}
	return (0);
}
