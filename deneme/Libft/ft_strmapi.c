/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:25:02 by musisman          #+#    #+#             */
/*   Updated: 2024/10/29 04:02:03 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	size_t	i;

	i = 0;
	a = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!a)
		return (NULL);
	while (i < ft_strlen(s))
	{
		a[i] = f(i, (char)s[i]);
		i++;
	}
	return (a);
}
