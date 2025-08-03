/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:12:38 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:12:38 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_single_quote(char *token, int i, char **res, int one)
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
	if (one == 0 && *res)
		*res = ft_strjoin(*res, " ");
	return (i);
}

int	handle_double_quote(const char *token, int i, char **res, t_expand *info)
{
	char	*part;
	char	*joined;
	int		start;

	i++;
	start = i;
	while (token[i] && token[i] != '"')
		i++;
	part = ft_substr(token, start, i - start);
	joined = expand_dollar(part, info);
	*res = ft_strjoin(*res, joined);
	if (token[i] == '"')
		i++;
	if (info->first == 0 && *res)
		*res = ft_strjoin(*res, " ");
	return (i);
}

int	handle_plain_text(char *token, int i, char **res, t_expand *info)
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
	return (i);
}

char	*expand(char *token, t_env *env, int exit_code, int first)
{
	t_expand	info;
	char		*res;
	int			i;

	info.env_list = env;
	info.exit_code = exit_code;
	info.first = first;
	i = 0;
	res = ft_calloc(1, 1);
	while (token[i])
	{
		if (token[i] == '\'')
			i = handle_single_quote(token, i, &res, first);
		else if (token[i] == '"')
			i = handle_double_quote(token, i, &res, &info);
		else
			i = handle_plain_text(token, i, &res, &info);
	}
	return (res);
}

int	expand_args(t_command *cmd, t_env *env, int exit_code)
{
	t_redirect	*redir;
	int			i;

	while (cmd)
	{
		i = -1;
		while (cmd->av && cmd->av[++i])
			cmd->av[i] = expand(cmd->av[i], env, exit_code, i);
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type != 4 && redir->filename)
				redir->filename = expand(redir->filename, env, exit_code, 1);
			else if (redir->filename)
				here_doc_no_expand(&redir->filename, 0, 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
