/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:38:32 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:40:17 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmini.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = ft_malloc(len + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}
