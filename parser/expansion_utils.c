/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:16:10 by musisman          #+#    #+#             */
/*   Updated: 2025/06/05 20:16:10 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_var_name(const char *str, size_t *i)
{
	size_t	start;
	char	*var;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	return (var);
}

static void	handle_exit_code(char **res, int *i, int last_exit)
{
	char	*tmp;

	tmp = ft_itoa(last_exit);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	*i += 2;
}

static void	handle_env_var(char **res, const char *s, size_t *i)
{
	char	*tmp;
	char	*env_value;

	tmp = extract_var_name(s, i);
	env_value = getenv(tmp);
	if (env_value)
		*res = ft_strjoin_free(*res, env_value);
	else
		*res = ft_strjoin_free(*res, "");
	free(tmp);
}

static void	handle_env_or_positional(char **res, const char *s, size_t *i)
{
	if (ft_isalpha(s[*i]) || s[*i] == '_')
		handle_env_var(res, s, i);
	else if (ft_isdigit(s[*i]))
		(*i)++;
	else
	{
		*res = ft_strjoin_char(*res, '$');
		if (s[*i])
			*res = ft_strjoin_char(*res, s[(*i)++]);
	}
}

char	*expand_dollar(const char *s, int last_exit)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
				handle_exit_code(&res, (int *)&i, last_exit);
			else
				handle_env_or_positional(&res, s, &i);
		}
		else
			res = ft_strjoin_char(res, s[i++]);
	}
	return (res);
}
