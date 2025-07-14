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

int	handle_single_quote(char *token, int i, char **res)
{
	int	start;

	i++;
	start = i;
	while (token[i] && token[i] != '\'')
		i++;
	*res = append_substring(*res, token, start, i);
	if (token[i] == '\'')
		i++;
	return (i);
}

int	handle_double_quote(char *token, int i, char **res, int last_exit)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	i++;
	start = i;
	while (token[i] && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, last_exit);
	*res = ft_strjoin_free(*res, tmp2);
	free(tmp);
	if (token[i] == '"')
		i++;
	return (i);
}

int	handle_plain_text(char *token, int i, char **res, int last_exit)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	start = i;
	while (token[i] && token[i] != '\'' && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, last_exit);
	*res = ft_strjoin_free(*res, tmp2);
	free(tmp);
	return (i);
}

char	*expand_token(const char *token, int last_exit)
{
	char	*res;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
	res = ft_calloc(1, 1);
	while (token[i])
	{
		if (token[i] == '\'')
			i = handle_single_quote((char *)token, i, &res);
		else if (token[i] == '"')
			i = handle_double_quote((char *)token, i, &res, last_exit);
		else
			i = handle_plain_text((char *)token, i, &res, last_exit);
	}
	return (res);
}

int	expand_args(t_command *cmd, int last_exit, int i)
{
	char		*tmp;
	t_redirect	*redir;

	while (cmd)
	{
		i = -1;
		while (cmd->av && cmd->av[++i])
		{
			tmp = expand_token(cmd->av[i], last_exit);
			free(cmd->av[i]);
			cmd->av[i] = tmp;
		}
		redir = cmd->redir;
		while (redir)
		{
			if (redir->filename)
			{
				tmp = expand_token(redir->filename, last_exit);
				free(redir->filename);
				redir->filename = tmp;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

