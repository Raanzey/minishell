/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:16:15 by musisman          #+#    #+#             */
/*   Updated: 2025/06/05 09:16:15 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_token(const char *token, int last_exit)
{
	size_t	i;
	char	*res;
	char	*tmp;
	char	quote;

	if (!token)
		return (NULL);
	i = 0;
	res = ft_calloc(1, 1);
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
			{
				if (quote == '"')
				{
					tmp = expand_dollar((char[]){token[i], 0}, last_exit);
					res = ft_strjoin_free(res, tmp);
					free(tmp);
				}
				else
					res = ft_strjoin_char(res, token[i]);
				i++;
			}
			if (token[i] == quote)
				i++;
		}
		else
		{
			tmp = expand_dollar((char[]){token[i], 0}, last_exit);
			res = ft_strjoin_free(res, tmp);
			free(tmp);
			i++;
		}
	}
	return (res);
}


char	**expand_args(char **tokens, int last_exit)
{
	char	**expanded;
	int		i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
		i++;
	expanded = ft_calloc(i + 1, sizeof(char *));
	if (!expanded)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		expanded[i] = ft_strdup(expand_token(tokens[i], last_exit));
		if (!expanded[i])
		{
			free_tokens(expanded);
			return (NULL);
		}
		i++;
	}
	expanded[i] = NULL;
	return (expanded);
}
