/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:20:53 by musisman          #+#    #+#             */
/*   Updated: 2025/05/29 17:20:53 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	skip_space(const char *s, size_t i)
{
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (i);
}

size_t	redirect(char **tokens, const char *s, size_t *i, size_t k)
{
	if ((s[*i] == '<' && s[*i + 1] == '<')
		|| (s[*i] == '>' && s[*i + 1] == '>'))
	{
		tokens[k] = ft_substr(s, *i, 2);
		*i += 2;
	}
	else
	{
		tokens[k] = ft_substr(s, *i, 1);
		(*i)++;
	}
	return (k + 1);
}
