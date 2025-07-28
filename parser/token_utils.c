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

int	skip_space(const char *s, int i)
{
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (i);
}

int	redirect(char **tokens, const char *s, int *i, int k)
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
