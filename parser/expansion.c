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

int	handle_double_quote(char *token, int i, char **res, int exit_code)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	i++;
	start = i;
	while (token[i] && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, exit_code);
	*res = ft_strjoin(*res, tmp2);
	// free(tmp);
	if (token[i] == '"')
		i++;
	return (i);
}

int	handle_plain_text(char *token, int i, char **res, int exit_code)
{
	char	*tmp;
	char	*tmp2;
	int		start;

	start = i;
	while (token[i] && token[i] != '\'' && token[i] != '"')
		i++;
	tmp = ft_substr(token, start, i - start);
	tmp2 = expand_dollar(tmp, exit_code);
	*res = ft_strjoin(*res, tmp2);
	// free(tmp);
	return (i);
}

char	*expand_token(const char *token, int exit_code)
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
			i = handle_double_quote((char *)token, i, &res, exit_code);
		else
			i = handle_plain_text((char *)token, i, &res, exit_code);
	}
	return (res);
}

int	expand_args(t_command *cmd, int exit_code)
{
	t_redirect	*redir;
	int			i;

	while (cmd)
	{
		i = -1;
		while (cmd->av && cmd->av[++i])
			expand_and_replace(&cmd->av[i], exit_code);
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type != 4 && redir->filename)
				expand_and_replace(&redir->filename, exit_code);
			else if (redir->filename)
				here_doc_no_expand(&redir->filename, 0, 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
