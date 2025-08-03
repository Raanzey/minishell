/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_extra_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:49:56 by musisman          #+#    #+#             */
/*   Updated: 2025/08/03 15:43:43 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_single_quote_redir(char *token, int i, char **res)
{
	char	*part;
	int		start;

	start = ++i;
	while (token[i] && token[i] != '\'')
		i++;
	part = ft_substr(token, start, i - start);
	*res = ft_strjoin(*res, part);
	if (token[i] == '\'')
		i++;
	return (i);
}

int	handle_double_quote_redir(const char *token, int i, char **res,
		t_expand *info)
{
	char	*part;
	char	*joined;
	int		start;

	start = ++i;
	while (token[i] && token[i] != '"')
		i++;
	part = ft_substr(token, start, i - start);
	joined = expand_dollar(part, info);
	*res = ft_strjoin(*res, joined);
	if (token[i] == '"')
		i++;
	return (i);
}

int	handle_plain_text_redir(char *token, int i, char **res, t_expand *info)
{
	char	*part;
	char	*joined;
	int		start;

	start = i;
	while (token[i] && token[i] != '\'' && token[i] != '"')
		i++;
	part = ft_substr(token, start, i - start);
	joined = expand_dollar(part, info);
	*res = ft_strjoin(*res, joined);
	if (!*res[0])
		return (err_noext(ft_strjoin(token, " :"), ERR_RDR, 0, -1));
	return (i);
}

char	*exp_redir(char *token, t_env *env, int exit_code)
{
	t_expand	info;
	char		*res;
	int			i;

	info.env_list = env;
	info.exit_code = exit_code;
	info.first = 0;
	i = 0;
	res = ft_calloc(1, 1);
	while (token[i])
	{
		if (token[i] == '\'')
			i = handle_single_quote_redir(token, i, &res);
		else if (token[i] == '"')
			i = handle_double_quote_redir(token, i, &res, &info);
		else
		{
			i = handle_plain_text_redir(token, i, &res, &info);
			if (i == -1)
				return (NULL);
		}
	}
	return (res);
}
