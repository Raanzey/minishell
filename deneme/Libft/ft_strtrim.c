/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:07:07 by musisman          #+#    #+#             */
/*   Updated: 2024/10/29 00:02:17 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;
	char	*a;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len_s1 = ft_strlen(s1);
	while (len_s1 > i && ft_strchr(set, s1[len_s1 - 1]))
		len_s1--;
	a = ft_calloc(len_s1 - i + 1, sizeof(char));
	if (!a)
		return (NULL);
	ft_memcpy(a, s1 + i, len_s1 - i);
	return (a);
}
