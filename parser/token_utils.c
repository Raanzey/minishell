#include "../minishell.h"

size_t	skip_space(const char *s, size_t i)
{
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (i);
}

size_t	skip_word_count(const char *s, size_t i)
{
	while (s[i] && !(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		&& s[i] != '<' && s[i] != '>' && s[i] != '|')
		i++;
	return (i);
}

size_t	skip_word(const char *s, size_t i)
{
	while (s[i] && !(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		&& s[i] != '<' && s[i] != '>' && s[i] != '|')
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
