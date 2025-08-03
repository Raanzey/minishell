/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:16:50 by musisman          #+#    #+#             */
/*   Updated: 2025/08/03 15:30:22 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quotes_control(const char *s, int *i)
{
	char	quote;

	if (s[*i] == '"' || s[*i] == '\'')
	{
		quote = s[(*i)++];
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] == quote)
		{
			(*i)++;
			return (0);
		}
		else
			return (err_noext(ft_strjoin_char(ERR_QUOTE, quote), 0, 0, 2));
	}
	(*i)++;
	return (0);
}

static int	token_count(const char *s, int tc, int i, char redir)
{
	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			redir = s[i++];
			if (s[i] == redir && s[i] != '|')
				i++;
		}
		else
		{
			while (s[i] && !(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)
					|| s[i] == '<' || s[i] == '>' || s[i] == '|'))
			{
				if (quotes_control(s, &i))
					return (-1);
			}
		}
		tc++;
	}
	return (tc);
}

static int	handle_word(char **tokens, const char *s, int *i, int k)
{
	int	start;

	start = *i;
	while (s[*i] && !(s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13)
			|| s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
		quotes_control(s, i);
	tokens[k] = ft_substr(s, start, *i - start);
	return (k + 1);
}

char	**tokenizer(const char *s)
{
	int		i;
	int		k;
	int		total;
	char	**tokens;

	i = 0;
	k = 0;
	total = token_count(s, 0, 0, 0);
	tokens = ft_calloc(total + 1, sizeof(char *));
	if (!tokens || total == -1)
		return (NULL);
	while (s[i] && total != 0)
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			k = redirect(tokens, s, &i, k);
		else
			k = handle_word(tokens, s, &i, k);
	}
	tokens[k] = NULL;
	return (tokens);
}
