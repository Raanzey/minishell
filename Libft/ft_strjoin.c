/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:53:24 by musisman          #+#    #+#             */
/*   Updated: 2024/10/24 17:42:31 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	a = ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i < ft_strlen(s1))
			a[i] = s1[i];
		else
			a[i] = s2[j++];
		i++;
	}
	return (a);
}
