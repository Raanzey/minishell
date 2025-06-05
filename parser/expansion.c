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

char	*expand_token(char *token, int last_exit)
{
	char	*tmp;
	char	*res;

	if (!token)
		return (NULL);
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (remove_quotes(token));
	if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		tmp = remove_quotes(token);
		res = expand_dollar(tmp, last_exit);
		free(tmp);
		return (res);
	}
	return (expand_dollar(token, last_exit));
}

void	expand_args(t_command *cmd, int last_exit)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->av && cmd->av[i])
		{
			tmp = expand_token(cmd->av[i], last_exit);
			free(cmd->av[i]);
			cmd->av[i] = tmp;
			i++;
		}
		cmd = cmd->next;
	}
}

void	expand_redirections(t_command *cmd, int last_exit)
{
	t_redirect	*r;
	char		*tmp;

	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			tmp = expand_token(r->filename, last_exit);
			free(r->filename);
			r->filename = tmp;
			r = r->next;
		}
		cmd = cmd->next;
	}
}
