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

void	handle_exit_code(char **res, int *i, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	*res = ft_strjoin(*res, tmp);
	*i += 1;
}

void	handle_env_var(char **res, const char *s, size_t *i, t_env *env_list)
{
	char	*tmp;
	char	*env_value;

	tmp = extract_var_name(s, i);
	env_value = get_env_value(env_list, tmp);
	if (env_value)
		*res = ft_strjoin(*res, env_value);
	else
		*res = ft_strjoin(*res, "");
}

void	handle_env_or_pos(char **res, const char *s, size_t *i, t_expand *info)
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
			i++;
			if (s[i] == '?')
				handle_exit_code(&res, (int *)&i, info->exit_code);
			else
				handle_env_or_pos(&res, s, &i, info);
		}
		else
			res = ft_strjoin_char(res, s[i++]);
	}
	return (res);
}
