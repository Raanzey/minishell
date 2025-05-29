/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:16:50 by musisman          #+#    #+#             */
/*   Updated: 2025/05/29 18:00:43 by musisman         ###   ########.fr       */
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
	if (total == 0)
		return (NULL);//TODO error durumu
	tokens = ft_calloc(total + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (s[i])
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


















int	is_operator(char *s)
{
	return (!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3)
		|| !ft_strncmp(s, "|", 2));
}

int	is_redirection(char *s)
{
	return (!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3));
}

int	check_syntax(char **tokens)
{
	size_t i = 0;

	// if (!tokens || !tokens[0])
	// 	return (error("syntax error: empty command\n"));

	// if (!ft_strncmp(tokens[0], "|", 2))
	// 	return (error("syntax error near unexpected token `|'\n"));

	while (tokens[i])
	{
		// Pipe + pipe / pipe + redirection
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (!tokens[i + 1])
				return (error("syntax error: trailing pipe `|'\n"));
			if (is_operator(tokens[i + 1]))
				return (error("syntax error near unexpected token after `|'\n"));
		}
		// Redirection yalnız veya peş peşe operatorle gelmişse
		else if (is_redirection(tokens[i]))
		{
			if (!tokens[i + 1])
				return (error("syntax error: missing file after redirection\n"));
			if (is_operator(tokens[i + 1]))
				return (error("syntax error near unexpected token after redirection\n"));
		}
		i++;
	}
	return (1);
}

size_t redirect_error(char **tokens, int i)
{
	if (!(ft_srtrncmp("<", tokens[i], 2) && ft_srtrncmp("<<", tokens[i], 3) 
			&& ft_srtrncmp(">", tokens[i], 2) && ft_srtrncmp(">>", tokens[i], 3)))
			{
				if (!(ft_srtrncmp("<", tokens[i + 1], 2) && ft_srtrncmp("<<", tokens[i + 1], 3) 
					&& ft_srtrncmp(">", tokens[i + 1], 2) && ft_srtrncmp(">>", tokens[i + 1], 3)))
					{
						error(ERR_ARG); // token bekleniyor
						return (0);
					}
			}
	else
		return (1);
}

size_t pipe_error(char **tokens, int i)
{
	return (1);
}

int	handle_error(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (!redirect_error(tokens, i))
			return (0);
		if (!pipe_error(tokens, i))
			return (0);
	}
	return (1);
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