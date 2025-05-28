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


static size_t	token_count(const char *s, size_t count, size_t i, char redirect)
{
	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			redirect = s[i++];
			if (s[i] == redirect)
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

		count++;
	}
	return (count);
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
		return (NULL);  //TODO error durumu
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
