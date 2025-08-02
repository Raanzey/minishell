/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_extra_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:57:49 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:38:08 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_substring(char *res, const char *src, int one, int end)
{
	char	*part;
	char	*new_res;

	part = ft_substr(src, one, end - one);
	new_res = ft_strjoin(res, part);
	return (new_res);
}

void	expand_and_replace(char **str, t_env *env, int exit_code, int first)
{
	char	*tmp;

	tmp = expand_token(*str, env, exit_code, first);
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
	*target = res;
}
