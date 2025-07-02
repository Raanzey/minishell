/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:16:50 by musisman          #+#    #+#             */
/*   Updated: 2025/07/02 18:39:59 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quotes_control(const char *s, size_t *i)
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
			return (1);
		}
		else
			return (0);
	}
	(*i)++;
	return (1);
}

static size_t	token_count(const char *s, size_t tc, size_t i, char redir)
{
	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			redir = s[i++];
			if (s[i] == redir)
				i++;
		}
		else
		{
			while (s[i] && !(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)
					|| s[i] == '<' || s[i] == '>' || s[i] == '|'))
			{
				if (!quotes_control(s, &i))
					return (0);
			}
		}
		tc++;
	}
	return (tc);
}

static size_t	handle_word(char **tokens, const char *s, size_t *i, size_t k)
{
	size_t	start;

	start = *i;
	while (s[*i] && !(s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13)
			|| s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		if (!quotes_control(s, i))
			return (0);
	}
	tokens[k] = ft_substr(s, start, *i - start);
	return (k + 1);
}

char	**tokenizer(const char *s)
{
	size_t	i;
	size_t	k;
	size_t	total;
	char	**tokens;

	i = 0;
	k = 0;
	total = token_count(s, 0, 0, 0);
	tokens = ft_calloc(total + 1, sizeof(char *));
	if (!tokens)
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


// waow

// musisman@k1m32s04:~/Desktop/minishell$ cat <in.txt | grep a < out.txt 
// main.c
// Makefile
// parser
// main.c
// Makefile
// parser
// main.c
// Makefile
// parser
// main.c
// Makefile
// parser
// main.c
// Makefile
// parser
// main.c
// Makefile
// parser
// musisman@k1m32s04:~/Desktop/minishell$ cat <in.txt | grep a
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa