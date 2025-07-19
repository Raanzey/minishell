/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisman <<msisman@student.42.fr>>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:06:20 by musisman          #+#    #+#             */
/*   Updated: 2024/10/31 16:23:27 by msisman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	world_count(char const *s, char c)
{
	size_t	wc;
	size_t	i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			wc++;
		}
	}
	return (wc);
}

static size_t	control(char const *s, size_t start, size_t i)
{
	if (s[start + i])
		return (1);
	return (0);
}

static void	free_tab(char **sp)
{
	size_t	i;

	i = 0;
	if (sp)
	{
		while (sp[i])
		{
			free(sp[i]);
			i++;
		}
		free(sp);
	}
}

static char	**last_sp(char **sp, char const *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	wc;

	i = 0;
	start = 0;
	wc = 0;
	while (s[start])
	{
		i = 0;
		while (s[start + i] && s[start + i] != c)
			i++;
		if (i > 0)
		{
			sp[wc] = ft_substr(s, start, i);
			if (!sp[wc])
			{
				free_tab(sp);
				return (NULL);
			}
			wc++;
		}
		start += i + control(s, start, i);
	}
	return (sp);
}

char	**ft_split(char const *s, char c)
{
	char	**sp;
	size_t	wc;

	wc = world_count(s, c);
	sp = ft_calloc(wc + 1, sizeof(char *));
	if (!sp)
		return (NULL);
	if (!last_sp(sp, s, c))
		return (NULL);
	return (sp);
}
