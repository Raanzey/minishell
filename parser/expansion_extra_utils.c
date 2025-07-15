/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_extra_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:57:49 by musisman          #+#    #+#             */
/*   Updated: 2025/07/15 18:53:41 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = c;
	res[len + 1] = '\0';
	free(s);
	return (res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	free(s1);
	return (res);
}

char	*append_substring(char *res, const char *src, int one, int end)
{
	char	*part;
	char	*new_res;

	part = ft_substr(src, one, end - one);
	new_res = ft_strjoin_free(res, part);
	free(part);
	return (new_res);
}

void	expand_and_replace(char **str, int last_exit)
{
	char	*tmp;

	tmp = expand_token(*str, last_exit);
	free(*str);
	*str = tmp;
}

void	here_doc_no_expand(char **target, size_t i, size_t j)
{
	char	*res;
	char	quote;

	if (!*target)
		return ;
	res = ft_calloc(ft_strlen(*target) + 1, 1);
	if (!res)
		return ;
	while ((*target)[i])
	{
		if ((*target)[i] == '\'' || (*target)[i] == '"')
		{
			quote = (*target)[i++];
			while ((*target)[i] && (*target)[i] != quote)
				res[j++] = (*target)[i++];
			if ((*target)[i] == quote)
				i++;
		}
		else
			res[j++] = (*target)[i++];
	}
	free(*target);
	*target = res;
}
