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

char	*expand_token(char *token, int last_exit)
{
	char	*tmp;
	char	*res;

	if (!token)
		return (NULL);
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (remove_quotes(token));
	if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		tmp = remove_quotes(token);
		res = expand_dollar(tmp, last_exit);
		free(tmp);
		return (res);
	}
	return (expand_dollar(token, last_exit));
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
