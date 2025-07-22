/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:55:39 by musisman          #+#    #+#             */
/*   Updated: 2025/07/22 16:15:11 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s, char *buffer)
{
	char	*a;
	size_t	i;
	size_t	j;

	if (!s)
	{
		s = malloc(1);
		s[0] = '\0';
	}
	a = malloc(ft_strlen(s) + ft_strlen(buffer) + 1);
	if (a == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		a[j] = s[j];
		j++;
	}
	while (buffer[i])
		a[j++] = buffer[i++];
	a[ft_strlen(s) + ft_strlen(buffer)] = '\0';
	free(s);
	return (a);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_line_s(char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	ptr = malloc(i + 2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		ptr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_new_line_s(char *s)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	a = malloc(ft_strlen(s) - i + 1);
	if (!a)
		return (NULL);
	i++;
	while (s[i])
		a[j++] = s[i++];
	a[j] = '\0';
	free(s);
	return (a);
}
