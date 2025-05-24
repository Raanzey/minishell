#include "../minishell.h"

static size_t	token_count(const char *s, size_t count, size_t i)
{
	char	quote;

	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else if ((s[i] == '<' && s[i + 1] == '<')
			|| (s[i] == '>' && s[i + 1] == '>'))
			i += 2;
		else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			i++;
		else
			i = skip_word_count(s, i);
		count++;
	}
	return (count);
}

static size_t	handle_word(char **tokens, const char *s, size_t *i, size_t k)
{
	size_t	start;

	start = *i;
	*i = skip_word(s, *i);
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
	total = token_count(s, 0, 0);
	tokens = ft_calloc(total + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '\"' || s[i] == '\'')
			k = quotes(tokens, s, &i, k);
		else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			k = redirect(tokens, s, &i, k);
		else
			k = handle_word(tokens, s, &i, k);
	}
	tokens[k] = NULL;
	return (tokens);
}
