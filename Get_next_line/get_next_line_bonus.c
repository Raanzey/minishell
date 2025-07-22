/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:08:31 by musisman          #+#    #+#             */
/*   Updated: 2024/12/31 16:54:06 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check(int b, char *s, char *buffer)
{
	if (b == -1)
	{
		free(buffer);
		free(s);
		return (0);
	}
	else if (b == 0 && (!s || s[0] == '\0'))
	{
		free(buffer);
		free(s);
		return (0);
	}
	return (1);
}

char	*ft_buffer_s(int fd, char *s)
{
	char	*buffer;
	int		b;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b = 1;
	while (ft_strchr(s, '\n') == 0 && b != 0)
	{
		b = read(fd, buffer, BUFFER_SIZE);
		if (!check(b, s, buffer))
			return (NULL);
		buffer[b] = '\0';
		s = ft_strjoin(s, buffer);
	}
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*ptr;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	s[fd] = ft_buffer_s(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	ptr = ft_line_s(s[fd]);
	s[fd] = ft_new_line_s(s[fd]);
	return (ptr);
}
