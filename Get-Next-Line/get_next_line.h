/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:06:49 by musyilma          #+#    #+#             */
/*   Updated: 2025/07/22 18:51:39 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

# include "../Libft/libft.h"

// char	*ft_substr(char *s, unsigned int start, size_t len);
// char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
// char	*ft_strchr(char *s, int c);
// char	*ft_strdup(char *src);
// void	*ft_calloc(size_t count, size_t size);

#endif