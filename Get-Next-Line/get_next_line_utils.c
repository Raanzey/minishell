/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:06:38 by musyilma          #+#    #+#             */
/*   Updated: 2025/07/22 18:50:20 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	*ft_calloc(size_t count, size_t size)
// {
// 	int				*a;
// 	size_t			len;
// 	size_t			i;
// 	unsigned char	*s;

// 	len = count * size;
// 	i = 0;
// 	a = malloc(count * size);
// 	if (a == NULL)
// 		return (NULL);
// 	s = (unsigned char *)a;
// 	while (i < len)
// 	{
// 		*(s + i) = 0;
// 		i++;
// 	}
// 	return (a);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char			*a;
// 	unsigned int	i;

// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (ft_calloc(sizeof(char), 1));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	a = malloc(len * sizeof(char) + 1);
// 	if (a == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		a[i] = s[start + i];
// 		i++;
// 	}
// 	a[i] = '\0';
// 	return (a);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		a;
// 	char	*str;
// 	int		i;
// 	int		b;

// 	a = ft_strlen(s1) + ft_strlen(s2);
// 	str = malloc(a + 1);
// 	if (str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	b = 0;
// 	while (s2[b])
// 	{
// 		str[i] = s2[b];
// 		b++;
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_strchr(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 		{
// 			return ((char *)s + i);
// 		}
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 	{
// 		return ((char *)s + i);
// 	}
// 	return (NULL);
// }

// char	*ft_strdup(char *src)
// {
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	dest = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
// 	if (!dest)
// 		return (0);
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }
