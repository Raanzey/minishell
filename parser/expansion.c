/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:16:15 by musisman          #+#    #+#             */
/*   Updated: 2025/06/05 09:16:15 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_single_quote(char *token, int i, char **res, int one)
{
	int	start;

	i++;
	start = i;
	while (token[i] && token[i] != '\'')
		i++;
	*res = append_substring(*res, token, start, i);
	if (token[i] == '\'')
		i++;
	if (one == 0 && *res)
		*res = ft_strjoin(*res, " ");
	return (i);
}

int	handle_double_quote(char *token, int i, char **res, t_expand *info)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	i++;
	start = i;
	while (token[i] && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, info);
	*res = ft_strjoin(*res, tmp2);
	if (token[i] == '"')
		i++;
	if (info->first == 0 && *res)
		*res = ft_strjoin(*res, " ");
	return (i);
}

int	handle_plain_text(char *token, int i, char **res, t_expand *info)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	start = i;
	while (token[i] && token[i] != '\'' && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, info);
	*res = ft_strjoin(*res, tmp2);
	return (i);
}

char	*expand_token(const char *token, t_env *env, int exit_code, int first)
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
			i = handle_single_quote((char *)token, i, &res, first);
		else if (token[i] == '"')
			i = handle_double_quote((char *)token, i, &res, &info);
		else
			i = handle_plain_text((char *)token, i, &res, &info);
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
			expand_and_replace(&cmd->av[i], env, exit_code, i);
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type != 4 && redir->filename)
				expand_and_replace(&redir->filename, env, exit_code, 1);
			else if (redir->filename)
				here_doc_no_expand(&redir->filename, 0, 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
