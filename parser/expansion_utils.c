/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:12:27 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:12:27 by musisman         ###   ########.fr       */
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

void	handle_env_var(char **res, const char *s, size_t *i, t_env *env_list)
{
	char	*var;
	char	*value;

	var = extract_var_name(s, i);
	value = get_env_value(env_list, var);
	if (value)
		*res = ft_strjoin(*res, value);
	else
		*res = ft_strjoin(*res, "");
}

void	handle_env(char **res, const char *s, size_t *i, t_expand *info)
{
	if (ft_isalpha(s[*i]) || s[*i] == '_')
		handle_env_var(res, s, i, info->env_list);
	else if (ft_isdigit(s[*i]))
		(*i)++;
	else
	{
		*res = ft_strjoin_char(*res, '$');
		if (s[*i])
			*res = ft_strjoin_char(*res, s[(*i)++]);
	}
}

char	*expand_dollar(char *s, t_expand *info)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[++i] == '?')
			{
				res = ft_strjoin(res, ft_itoa(info->exit_code));
				i++;
			}
			else
				handle_env(&res, s, &i, info);
		}
		else
			res = ft_strjoin_char(res, s[i++]);
	}
	return (res);
}

void	here_doc_no_expand(char **delimiter, size_t i, size_t j)
{
	char	*res;
	char	quote;

	if (!*delimiter)
		return ;
	res = ft_calloc(ft_strlen(*delimiter) + 1, 1);
	if (!res)
		return ;
	while ((*delimiter)[i])
	{
		if ((*delimiter)[i] == '\'' || (*delimiter)[i] == '"')
		{
			quote = (*delimiter)[i++];
			while ((*delimiter)[i] && (*delimiter)[i] != quote)
				res[j++] = (*delimiter)[i++];
			if ((*delimiter)[i] == quote)
				i++;
		}
		else
			res[j++] = (*delimiter)[i++];
	}
	*delimiter = res;
}
